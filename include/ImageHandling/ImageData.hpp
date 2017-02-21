#ifndef __BOS_IMAGEHANDLING_IMAGE_DATA_HPP__
#define __BOS_IMAGEHANDLING_IMAGE_DATA_HPP__

#include <vector>
#include <iostream>

#include "BOS.hpp"
#include "Pixel.hpp"
#include "Coordinate.hpp"

namespace BOS
{
	namespace imageHandling
	{
		// Class containing 3-byte RGB image data
		class ImageData
		{
		public:
			ImageData(uint32_t width, uint32_t height, std::vector<BOS::imageHandling::Pixel> data);
			const uint16_t	getWidth() const;
			const uint16_t	getHeight() const;
			const bos_shared_ptr<BOS::imageHandling::Pixel> getPixel(uint32_t w, uint32_t h) const;
			void setPixel(uint32_t w, uint32_t h, bos_shared_ptr<BOS::imageHandling::Pixel> pixel);
			const std::vector<BOS::imageHandling::Pixel> data() const;

		private:
			uint16_t	m_width;
			uint16_t	m_height;
			std::vector<BOS::imageHandling::Pixel>	m_data; 
		};	
	}
}

#endif