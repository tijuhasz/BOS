#include <boost/asio/io_service.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>

#include "ImageProcessing/Schlieren.hpp"
#include "ImageHandling/ImageData.hpp"
#include "ImageProcessing/ColorBox.hpp"
#include "Utilities/BOSException.hpp"
#include "Utilities/ProgressIndicator.hpp"

namespace BOS
{
	namespace imageProcessing
	{
		Schlieren::Schlieren(bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> settings)
		{
			m_settings = settings;
			initColorBox();
			initOffsetVector();
		}

		void Schlieren::initColorBox()
		{
			// size of color box = 2 * search distance + 1 to have a (0,0) pixel at the middle of the square
			m_colorBox = bos_make_shared<BOS::imageProcessing::ColorBox>(m_settings->searchDist * 2 + 1); 
		}

		void Schlieren::sendProgressPercent(uint16_t percent)
		{
			BOS::Utilities::ProgressIndicator::progressPercentage(percent);
		}

		void Schlieren::initOffsetVector()
		{
			/* Create a vector of coordinates starting with (0,0) and around this point, similar to this one:
			{{0,0},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},
			{-2,2},{-1,2},{0,2},{1,2},{2,2},{2,1},{2,0},{2,-1},{2,-2},{1,-2},{0,-2},{-1,-2},{-2,-2},{-2,-1},{-2,0},{-2,1} ...
			*/
			m_offsetVector.push_back(BOS::imageHandling::Coordinate(0,0));

			int32_t w, h;
			for(int32_t dist = 1; dist < m_settings->searchDist; ++dist)
			{
				w = dist;
				for(h = -dist; h <= dist; ++h)
				{
					BOS::imageHandling::Coordinate c1(w, h);
					m_offsetVector.push_back(c1);
					BOS::imageHandling::Coordinate c2(-w, h);
					m_offsetVector.push_back(c2);
				}
				h = dist;
				for(w = -dist; w <= dist; ++w)
				{
					BOS::imageHandling::Coordinate c1(w, h);
					m_offsetVector.push_back(c1);
					BOS::imageHandling::Coordinate c2(-w, h);
					m_offsetVector.push_back(c2);
				}
			}
		}

		void Schlieren::setReferenceImage(bos_shared_ptr<BOS::imageHandling::ImageData> referenceImage)
		{
			m_referenceImage = referenceImage;
		}

		void Schlieren::setProcessImage(bos_shared_ptr<BOS::imageHandling::ImageData> processImage)
		{
			m_processImage = processImage;
		}

		void Schlieren::createFinalImage()
		{
			if (m_finalImage) { Utilities::BOSException e("Result image already exists"); throw e; }
			if (!m_referenceImage) { Utilities::BOSException e("Cannot create result image if reference image is not set"); throw e; }
			if (!m_processImage) { Utilities::BOSException e("Cannot create result image if process image is not set"); throw e; }

			BOS::imageHandling::Pixel pixel; pixel.r = 0; pixel.g = 0; pixel.b = 0;
			std::vector<BOS::imageHandling::Pixel> imgPixelData( m_processImage->getWidth() * m_processImage->getHeight(), pixel );
			m_finalImage = bos_make_shared<BOS::imageHandling::ImageData>(m_processImage->getWidth(), m_processImage->getHeight(), imgPixelData);
		}

		bos_shared_ptr<BOS::imageHandling::ImageData> Schlieren::getFinalImage()
		{
			if (m_finalImage) return m_finalImage;
			else return NULL;
		}

		void Schlieren::launchSchlierenProcessingInCpuThreads()
		{
			if (!m_referenceImage) { Utilities::BOSException e("Cannot generate result image if reference image is not set"); throw e; }
			if (!m_processImage) { Utilities::BOSException e("Cannot generate result image if process image is not set"); throw e; }

			// delete final image if set and create new one
			if (m_finalImage) m_finalImage.reset();
			createFinalImage();

			boost::thread_group threadpool;

			uint16_t numThreads = 1;
			 uint32_t imgHeight = m_referenceImage->getHeight();
			 if (imgHeight < 500) numThreads = 1;
			 else if (imgHeight < 1500) numThreads = 4;
			 else numThreads = 8;

			 // height start and end values for processing
			 // begin processing from a height of searchDist, 
			 // because otherwise we would search outside of the image (at a height < 0)
			 // end processing by imgHeight - searchDist - boxH, 
			 // not to reference image at a height > imgHeight
			 uint32_t processHeightBeg = m_settings->searchDist; 
			 uint32_t processHeightEnd = imgHeight - m_settings->searchDist - m_settings->boxH;

			 // height interval to be processed by a single thread
			 float threadHeight = (float)(processHeightEnd - processHeightBeg) / numThreads;

			 for (uint16_t threadNum = 0; threadNum < numThreads; ++threadNum) {
				uint32_t hBeg = processHeightBeg + (uint32_t)(threadNum * threadHeight);
				uint32_t hEnd = hBeg + (uint32_t)(threadHeight);

				threadpool.create_thread( 
					boost::bind( &Schlieren::generateFinalImageSectionThread, this, hBeg, hEnd) 
				);
			}

			threadpool.join_all();
		}

		void Schlieren::generateFinalImageSectionThread(uint32_t hBeg, uint32_t hEnd) {
			try {
				// iterate reference matrix in reference image
				// wR, hR are current width and height values of upper left corner of reference matrix in reference image
				int_least32_t wBeg = m_settings->searchDist;
				int_least32_t wEnd = m_referenceImage->getWidth() - m_settings->searchDist - m_settings->boxW;

				// refCoord holds the current width and height values of upper left corner of reference matrix in reference image
				bos_shared_ptr<BOS::imageHandling::Coordinate> refCoord = bos_make_shared<BOS::imageHandling::Coordinate>
					(0,0);

				for (int_least32_t hRef = hBeg; hRef < hEnd; hRef += m_settings->boxH) {
					sendProgressPercent((hRef-hBeg) * 100 / (hEnd-hBeg));
					for (int_least32_t wRef = wBeg; wRef < wEnd; wRef += m_settings->boxW) {
						refCoord->setCoord(wRef, hRef);
						// iterate process matrix around position of reference matrix
						bool notFound = true;
						uint32_t minResult = INT32_MAX;
						int_least32_t wOffset = 0; // width offset where match is found
						int_least32_t hOffset = 0; // height offset where match is found

						for (uint16_t curOffset = 0; curOffset < m_offsetVector.size() && notFound; ++curOffset)
						{
							uint32_t result = compareMatrices(wRef, hRef, wRef + m_offsetVector[curOffset].w, hRef + m_offsetVector[curOffset].h );
							if (result < minResult)
							{
								minResult = result;
								wOffset = m_offsetVector[curOffset].w;
								hOffset = m_offsetVector[curOffset].h;
								if (!m_settings->compareAll && minResult < m_settings->matchThreshold) notFound = false; // found a good-enough match so stop searching
							}
						}

						if (minResult < m_settings->matchThreshold) colorFinalImageAt(wRef, hRef, wOffset, hOffset);
					}
				}
			} catch (std::exception& e) {
					std::cout << "EXCEPTION: " << e.what() << std::endl;
			} catch (...) {
					std::cout << "Unknown EXCEPTION " << std::endl;
			}
			return;
		}

		void Schlieren::generateFinalImage()
		{
			//// iterate reference matrix in reference image
			//// wR, hR are current width and height values of upper left corner of reference matrix in reference image
			//bos_shared_ptr<BOS::imageHandling::Coordinate> refCoord = bos_make_shared<BOS::imageHandling::Coordinate>
			//	(0,0);
			//bos_shared_ptr<BOS::imageHandling::Coordinate> endCoord = bos_make_shared<BOS::imageHandling::Coordinate>
			//	(m_referenceImage->getWidth() - m_settings->searchDist - m_settings->boxW,
			//	 m_referenceImage->getHeight() - m_settings->searchDist - m_settings->boxH);
			//for (int_least32_t wRef = m_settings->searchDist; wRef < endCoord->w; wRef += m_settings->boxW)
			//for (int_least32_t hRef = m_settings->searchDist; hRef < endCoord->h; hRef += m_settings->boxH) 
			//{
			//	refCoord->setCoord(wRef, hRef);
			//	// iterate process matrix around position of reference matrix
			//	bool notFound = true;
			//	uint32_t minResult = INT32_MAX;
			//	int_least32_t wOffset = 0; // width offset where match is found
			//	int_least32_t hOffset = 0; // height offset where match is found

			//	for (uint16_t curOffset = 0; curOffset < m_offsetVector.size() && notFound; ++curOffset)
			//	{
			//		uint32_t result = compareMatrices(wRef, hRef, wRef + m_offsetVector[curOffset].w, hRef + m_offsetVector[curOffset].h );
			//		if (result < minResult)
			//		{
			//			minResult = result;
			//			wOffset = m_offsetVector[curOffset].w;
			//			hOffset = m_offsetVector[curOffset].h;
			//			if (!m_settings->compareAll && minResult < m_settings->matchThreshold) notFound = false; // found a good-enough match so stop searching
			//		}
			//	}

			//	if (minResult < m_settings->matchThreshold) colorFinalImageAt(wRef, hRef, wOffset, hOffset);

			//	sendProgressPercent(wRef * 100 / m_referenceImage->getWidth());
			//}

			std::cout << "Function generateFinalImage() is deprecated" << std::endl;
			return;
		}

		uint32_t Schlieren::compareMatrices(uint16_t wRef, uint16_t hRef, uint16_t wProc, uint16_t hProc)
		{
			uint32_t result = 0; 
			uint32_t partialThreshold = 0;
			uint32_t partialThrStep = 4 * MAX_PERMISSIBLE_COLOR_DIFFERENCE_OF_PIXELS * BOS::imageHandling::BitmapImage::BYTES_PER_PIXEL;

			for(uint16_t w = 0; w < m_settings->boxW; ++w)
			for(uint16_t h = 0; h < m_settings->boxH; ++h) {
				result += pixelDistance( m_referenceImage->getPixel(wRef+w, hRef+h), m_processImage->getPixel(wProc+w, hProc+h) );
				partialThreshold += partialThrStep;
				// quit comparison early if pixels are very different
				if (result > partialThreshold) { 
					result = m_settings->matchThreshold + 1;
					return result;
				}
			}
			return result;
		}

		uint32_t Schlieren::pixelDistance(bos_shared_ptr<BOS::imageHandling::Pixel> p1, bos_shared_ptr<BOS::imageHandling::Pixel> p2)
		{
			return (abs(p1->b - p2->b) + abs(p1->g - p2->g) + abs(p1->r - p2->r));
		}

		void Schlieren::colorFinalImageAt(uint16_t wAt, uint16_t hAt, int_least32_t wOffset, int_least32_t hOffset)
		{
			bos_shared_ptr<BOS::imageHandling::Pixel> colorPixel = m_colorBox->getPixelFromMiddle(wOffset, hOffset);

			for(uint16_t w = wAt; w < wAt + m_settings->boxW; ++w)
			for(uint16_t h = hAt; h < hAt + m_settings->boxH; ++h)
				m_finalImage->setPixel(w,h, colorPixel);
		}

		bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> Schlieren::getSettings()
		{
			return m_settings;
		}

		void Schlieren::setSettings(bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> settings)
		{
			m_settings = settings;
		}

	}
}