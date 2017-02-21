#include "ImageHandling/ImageData.hpp"

namespace BOS
{
	namespace imageHandling
	{

		ImageData::ImageData(uint32_t width, uint32_t height, std::vector<BOS::imageHandling::Pixel> data):
			m_width(width),
			m_height(height),
			m_data(data)
		{ }

		const uint16_t ImageData::getWidth() const
		{
			return m_width;
		}

		const uint16_t ImageData::getHeight() const
		{
			return m_height;
		}

		const bos_shared_ptr<Pixel> ImageData::getPixel(uint32_t w, uint32_t h) const
		{
			bos_shared_ptr<BOS::imageHandling::Pixel> px = bos_make_shared<BOS::imageHandling::Pixel>(m_data[h * m_width + w]);
			return px;
		}

		void ImageData::setPixel(uint32_t w, uint32_t h, bos_shared_ptr<BOS::imageHandling::Pixel> pixel)
		{
			m_data[h * m_width + w] = *pixel;
		}

		const std::vector<BOS::imageHandling::Pixel> ImageData::data() const
		{
			return m_data;
		}
	}
}