#ifndef __BOS_IMAGEPROCESSING_SCHLIEREN_HPP__
#define __BOS_IMAGEPROCESSING_SCHLIEREN_HPP__

#include <string>
#include "ImageHandling/ImageData.hpp"
#include "ImageHandling/BitmapImage.hpp"
#include "ImageProcessing/ColorBox.hpp"

namespace BOS
{
	namespace imageProcessing
	{
		// scalar value, the maximum difference between the same color components of two pixels for the pixels to be considered equal
		// used when comparing pixels for schlieren processing to find matches
		const size_t MAX_PERMISSIBLE_COLOR_DIFFERENCE_OF_PIXELS = 7;
		const size_t MAX_OFFSET = 6; // maximum offset value to search for matches in process image
		const size_t MAX_OFFSET_NO = (MAX_OFFSET * 2 + 1) * (MAX_OFFSET * 2 + 1);

		struct SchlierenSettings 
		{
			SchlierenSettings(): boxW(5), boxH(5), searchDist(6), compareAll(false)
			{ matchThreshold = boxW * boxH * MAX_PERMISSIBLE_COLOR_DIFFERENCE_OF_PIXELS * BOS::imageHandling::BitmapImage::BYTES_PER_PIXEL; }
			SchlierenSettings(uint16_t boxW_, uint16_t boxH_, uint16_t searchDist_, bool compareAll_): 
				boxW(boxW_), boxH(boxH_), searchDist(searchDist_), compareAll(compareAll_)
			{ matchThreshold = boxW * boxH * MAX_PERMISSIBLE_COLOR_DIFFERENCE_OF_PIXELS * BOS::imageHandling::BitmapImage::BYTES_PER_PIXEL; }

			uint16_t boxW; // width of box used for comparison
			uint16_t boxH;  // height of box used for comparison
			uint16_t searchDist; // search distance for comparing box in reference image with box in process image (left, right, up and down from reference box)
			uint32_t matchThreshold; // threshold value for finding a good-enough match of pixel matrices, depends on boxW and boxH
			bool compareAll;
		};

		class Schlieren {
		public:
			Schlieren(bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> settings);
			void setReferenceImage(bos_shared_ptr<BOS::imageHandling::ImageData> referenceImage);
			void setProcessImage(bos_shared_ptr<BOS::imageHandling::ImageData> processImage);
			void generateFinalImage();
			bos_shared_ptr<BOS::imageHandling::ImageData> getFinalImage();

			bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> getSettings();
			void setSettings(bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> settings);

			void launchSchlierenProcessingInCpuThreads();

		private:
			void initColorBox();
			void initOffsetVector();
			void createFinalImage();
			uint32_t compareMatrices(uint16_t wR, uint16_t hR, uint16_t wP, uint16_t hP);
			uint32_t pixelDistance(bos_shared_ptr<BOS::imageHandling::Pixel> p1, bos_shared_ptr<BOS::imageHandling::Pixel> p2);
			void colorFinalImageAt(uint16_t wAt, uint16_t hAt, int_least32_t wDistance, int_least32_t hDistance);
			void sendProgressPercent(uint16_t percent);
			void generateFinalImageSectionThread(uint32_t hBeg, uint32_t hEnd);

			std::vector<BOS::imageHandling::Coordinate> m_offsetVector;
			bos_shared_ptr<BOS::imageHandling::ImageData> m_referenceImage;
			bos_shared_ptr<BOS::imageHandling::ImageData> m_processImage;
			bos_shared_ptr<BOS::imageHandling::ImageData> m_finalImage;
			bos_shared_ptr<BOS::imageProcessing::ColorBox> m_colorBox;
			bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> m_settings;
		};
	}
}
#endif