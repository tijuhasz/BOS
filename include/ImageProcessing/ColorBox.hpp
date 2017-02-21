#ifndef __BOS_IMAGEPROCESSING_COLORBOX_HPP__
#define __BOS_IMAGEPROCESSING_COLORBOX_HPP__

#include "BOS.hpp"
#include "ImageHandling/ImageData.hpp"

namespace BOS
{
	namespace imageProcessing
	{
		/**************************************************************************************
		* ColorBox: square box of color with white in the middle and different colors radiating
		* from the middle outwards in function of angle of radiation; saturated color is at the
		* edges of the box
		***************************************************************************************/
		class ColorBox {
		public:
			ColorBox(uint16_t size);
			const bos_shared_ptr<BOS::imageHandling::Pixel> getPixelAtAbsCoord(uint16_t w, uint16_t h) const; //get pixel value at coordinates from the upper left corner of image
			const bos_shared_ptr<BOS::imageHandling::Pixel> getPixelFromMiddle(int_least32_t wOffsetFromMiddle, int_least32_t hOffsetFromMiddle) const; // get pixel value at coordinates offset from the middle of image
			const bos_shared_ptr<BOS::imageHandling::ImageData> getImageData() const;

		private:
			void fillWithColor();

			bos_shared_ptr<BOS::imageHandling::ImageData> m_colorData;
			uint16_t m_size;
		};
	}

}

#endif