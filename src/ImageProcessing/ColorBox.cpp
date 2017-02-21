#include "ImageProcessing/ColorBox.hpp"
#include "ImageHandling/ImageData.hpp"
#include "Utilities/BOSException.hpp"

namespace BOS
{
	namespace imageProcessing
	{
		ColorBox::ColorBox(uint16_t size) : m_size(size)
		{
			if (m_size%2 == 0) { BOS::Utilities::BOSException e("Width of color box must be an odd number, " + std::to_string(size) + " given." ); throw e; }

			std::vector<BOS::imageHandling::Pixel> colorPixelData;
			colorPixelData.resize(size * size);
			m_colorData = bos_make_shared<BOS::imageHandling::ImageData>(m_size, m_size, colorPixelData);

			fillWithColor();
		}

		void ColorBox::fillWithColor()
		{
			float halfWidth = m_size / 2;

			bos_shared_ptr<BOS::imageHandling::Pixel> pixel = bos_make_shared<BOS::imageHandling::Pixel>();

			float maxColor = 255; // G - maximum value of saturated color
			float pixelRange = halfWidth; // M - number of pixels from 

			for(float y = 0; y < halfWidth; y++) {
				for(float x = 0; x < halfWidth; x++)   
				{
					if (x > y) {
						pixel->b = uint8_t(maxColor - maxColor/pixelRange * x);
						pixel->g = uint8_t(maxColor - maxColor/pixelRange/2 * y);
						pixel->r = uint8_t(maxColor);
					} else {
						pixel->b = uint8_t(maxColor - maxColor/pixelRange * y);
						pixel->g = uint8_t(maxColor + maxColor/pixelRange * (x/2-y));
						pixel->r = uint8_t(maxColor);
					}
					m_colorData->setPixel(halfWidth - y, halfWidth + x, pixel);
				}
			}
			 
		  for(int y = 0; y < pixelRange; y++) {
			 for(int x = 0; x < pixelRange; x++)  
			 {
				if (x > y) {
					pixel->b = uint8_t(maxColor - maxColor/pixelRange * x);
					pixel->g = uint8_t(maxColor);
					pixel->r = uint8_t(maxColor - maxColor/pixelRange * y);
				} else {
					pixel->b = uint8_t(maxColor - maxColor/pixelRange * x);
					pixel->g = uint8_t(maxColor + maxColor/pixelRange * (x-y));
					pixel->r = uint8_t(maxColor - maxColor/pixelRange * y);
				}
				m_colorData->setPixel(halfWidth + y, halfWidth + x, pixel);
			 }
		  }

		  for(int y = 0; y < pixelRange; y++) {
			 for(int x = 0; x < pixelRange; x++)  {
				if (x > y) {
					pixel->b = uint8_t(maxColor);
					pixel->g = uint8_t(maxColor - maxColor/pixelRange * x);
					pixel->r = uint8_t(maxColor - maxColor/pixelRange/2 * y);
				} else {
					pixel->b = uint8_t(maxColor);
					pixel->g = uint8_t(maxColor - maxColor/pixelRange * y);
					pixel->r = uint8_t(maxColor + maxColor/pixelRange * (x/2-y));
				}
				m_colorData->setPixel(halfWidth + y, halfWidth - x, pixel);
			 }
		  }

		  for(int y = 0; y < pixelRange; y++) {
			 for(int x = 0; x < pixelRange; x++)  {
				if (x > y) {
					pixel->b = uint8_t(maxColor - maxColor/pixelRange/2 * y);
					pixel->g = uint8_t(maxColor - maxColor/pixelRange * x);
					pixel->r = uint8_t(maxColor);
				} else {   
					pixel->b = uint8_t(maxColor + maxColor/pixelRange * (x/2-y));
					pixel->g = uint8_t(maxColor - maxColor/pixelRange * y);
					pixel->r = uint8_t(maxColor);
				}
				m_colorData->setPixel(halfWidth - y, halfWidth - x, pixel);
			 }
		  }

		}

		const bos_shared_ptr<BOS::imageHandling::ImageData> ColorBox::getImageData() const
		{
			return m_colorData;
		}

		const bos_shared_ptr<BOS::imageHandling::Pixel> ColorBox::getPixelAtAbsCoord(uint16_t w, uint16_t h) const
		{
			if (0 > w || w >= m_size) { 
				BOS::Utilities::BOSException e(DEBUG_INFO + "Width value out of range, " + std::to_string(w) + " given." ); throw e; }
			if (0 > h || h >= m_size) { BOS::Utilities::BOSException e(DEBUG_INFO + "Height value out of range:, " + std::to_string(h) + " given." ); throw e; }

			return m_colorData->getPixel(w, h);
		}

		const bos_shared_ptr<BOS::imageHandling::Pixel> ColorBox::getPixelFromMiddle(int_least32_t wOffsetFromMiddle, int_least32_t hOffsetFromMiddle) const
		{
			uint16_t middle = m_size/2; // if m_size is even, m_size/2 + h (=m_size/2) can be out of range of vector

			int_least32_t absCoordW = wOffsetFromMiddle + middle;
			int_least32_t absCoordH = hOffsetFromMiddle + middle;

			if (0 > absCoordW || absCoordW > m_size) { 
				BOS::Utilities::BOSException e(DEBUG_INFO + "Width value out of range, " + std::to_string(hOffsetFromMiddle) + " given." ); throw e; 
			}
			if (0 > absCoordH || absCoordH > m_size) { 
				BOS::Utilities::BOSException e(DEBUG_INFO + "Height value out of range:, " + std::to_string(hOffsetFromMiddle) + " given." ); throw e; 
			}

			return m_colorData->getPixel(absCoordW, absCoordH);
		}
	}

}
