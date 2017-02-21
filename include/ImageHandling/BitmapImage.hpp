#ifndef __BOS_IMAGEHANDLING_BITMAP_IMAGE_HPP__
#define __BOS_IMAGEHANDLING_BITMAP_IMAGE_HPP__

#include <string>
#include "ImageData.hpp"

namespace BOS
{
	namespace imageHandling
	{

		class BitmapImage {
		
		public:
			static const size_t HEADER_SIZE = 54; // size of bitmap header in bitmap file
			static const size_t BITMAPINFOHEADER_SIZE = 40; // size of bitmap info header in bitmap file
			static const size_t BITS_PER_PIXEL = 24; // this class only processes 24-bit bitmap files for now
			static const size_t NUMBER_OF_PLANES = 1; // number of planes in the image, must be 1
			static const size_t COMPRESSION_TYPE = 0; // compression type (0=none, 1=RLE-8, 2=RLE-4)
			static const size_t BYTES_PER_PIXEL = 3; // bytes per pixel

			BitmapImage();
			BitmapImage(const std::string& imageFilename);
			void loadImageFile(const std::string& imageFilename);
			void saveImageFile(const std::string& imageFilename);
			bos_shared_ptr<BOS::imageHandling::ImageData> getImageData();
			static void createImageFile(const std::string& imageFilename, const bos_shared_ptr<BOS::imageHandling::ImageData> imageData);

		private:
			std::string m_imageFilename;
			bos_shared_ptr<BOS::imageHandling::ImageData> m_imageData;
		
		};
	}
}
#endif