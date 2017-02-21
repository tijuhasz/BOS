#include "ImageHandling/ImageData.hpp"
#include "ImageHandling/BitmapImage.hpp"
#include "Utilities/BOSException.hpp"

#include <fstream>
#include <iostream>
#include <array>
#include <vector>

namespace BOS
{
	namespace imageHandling
	{

		void BitmapImage::loadImageFile(const std::string& imageFilename)
		{
			m_imageFilename = imageFilename;

			std::ifstream bmpStream(m_imageFilename, std::ios::binary);
			if (!bmpStream.is_open() || !bmpStream.good())
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile() returned on file: '" + m_imageFilename + "' - " + (std::string)strerror(errno);
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			// read header
			std::array<char, BOS::imageHandling::BitmapImage::HEADER_SIZE> header;
			bmpStream.read(header.data(), header.size());
			if (bmpStream.fail())
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile():bmpStream.read(header) returned: " + (std::string)strerror(errno);
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			auto fileSize = *reinterpret_cast<uint32_t *>(&header[2]);
			auto dataOffset = *reinterpret_cast<uint32_t *>(&header[10]); // header size
			auto width = *reinterpret_cast<uint32_t *>(&header[18]);
			auto height = *reinterpret_cast<uint32_t *>(&header[22]);
			auto bitsPerPixel = *reinterpret_cast<uint16_t *>(&header[28]);
			auto dataSize = *reinterpret_cast<uint32_t *>(&header[34]);
			if (dataSize != ((width * 3 + 3) & (~3)) * height)
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile() returned: Bitmap header data mismatch (width, height, dataSize)";
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			uint32_t rowPadded = dataSize/height;
			if (rowPadded != (width * bitsPerPixel / 8) + ((4 - ((width * bitsPerPixel / 8) % 4)) % 4))
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile() returned: Bitmap header data mismatch (dataSize, height, width, bitsPerPixel)";
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			// first and second char of bitmap file should be 'BM'
			if (header[0] != 'B' || header[1] != 'M')
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile() returned: First two bytes of file is not 'BM'";
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			// 24-bit bitmap files are processed only
			if (bitsPerPixel != BOS::imageHandling::BitmapImage::BITS_PER_PIXEL)
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile() returned: Only 24-bit bitmaps are processed";
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			std::vector<BOS::imageHandling::Pixel> imgPixelData;
			imgPixelData.resize(width * height);

			std::vector<char> rowCharData(rowPadded);
			std::size_t rowUnpadded = width * bitsPerPixel / 8;

			// read image data by row: read rowPadded number of bytes from file
			// BUT write only rowUnpadded number of bytes to imgPixelData => omit padding bytes
			for (uint16_t rowNo = 0; rowNo < height; ++rowNo)
			{
				bmpStream.read(rowCharData.data(), rowCharData.size());
				memcpy(&imgPixelData[rowNo * width], rowCharData.data(), rowUnpadded);
			}

			m_imageData = bos_make_shared<ImageData>(width, height, imgPixelData);

			bmpStream.close();
			if (bmpStream.fail())
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::loadImageFile():bmpStream.close() returned: " + (std::string)strerror(errno);
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}
		}

		void BitmapImage::saveImageFile(const std::string& imageFilename)
		{
			createImageFile(imageFilename, m_imageData);
		}

		void BitmapImage::createImageFile(const std::string& imageFilename, const bos_shared_ptr<BOS::imageHandling::ImageData> imageData)
		{
			std::ofstream saveFile(imageFilename, std::ofstream::binary);

			std::array<char, BOS::imageHandling::BitmapImage::HEADER_SIZE> header;
			header.fill(0);

			header[0] = 'B'; 
			header[1] = 'M';

			uint32_t dataOffset = BOS::imageHandling::BitmapImage::HEADER_SIZE;
			uint32_t infoHeaderSize = BOS::imageHandling::BitmapImage::BITMAPINFOHEADER_SIZE;
			uint32_t width = imageData->getWidth();
			uint32_t height = imageData->getHeight();
			uint16_t bitsPerPixel = BOS::imageHandling::BitmapImage::BITS_PER_PIXEL;
			uint32_t fileSize = width * height * BOS::imageHandling::BitmapImage::BITS_PER_PIXEL / 8 + BOS::imageHandling::BitmapImage::HEADER_SIZE;
			uint16_t numPlanes = BOS::imageHandling::BitmapImage::NUMBER_OF_PLANES;
			uint32_t compressionType = BOS::imageHandling::BitmapImage::COMPRESSION_TYPE;
			uint32_t padding = ((4 - ((width * 3) % 4)) % 4);;
			uint32_t imageDataSize = (width * 3 + padding) * height; 

			memcpy(&header[2], &fileSize, sizeof(fileSize));
			memcpy(&header[10], &dataOffset, sizeof(dataOffset));
			memcpy(&header[14], &infoHeaderSize, sizeof(infoHeaderSize));
			memcpy(&header[18], &width, sizeof(width));
			memcpy(&header[22], &height, sizeof(height));
			memcpy(&header[26], &numPlanes, sizeof(numPlanes));
			memcpy(&header[28], &bitsPerPixel, sizeof(bitsPerPixel));
			memcpy(&header[30], &compressionType, sizeof(compressionType));
			memcpy(&header[34], &imageDataSize, sizeof(imageDataSize));

			saveFile.write(header.data(), header.size());
			if (saveFile.fail())
			{
				std::string errorMsg = "BOS::imageHandling::BitmapImage::saveImageFile():saveFile.write(header) returned: " + (std::string)strerror(errno);
				BOS::Utilities::BOSException e(errorMsg);
				throw e;
			}

			if (padding == 0)
			{
				saveFile.write(reinterpret_cast<const char *>(&imageData->data()[0]), imageDataSize);
				if (saveFile.fail())
				{
					std::string errorMsg = "BOS::imageHandling::BitmapImage::saveImageFile():saveFile.write(data) returned: " + (std::string)strerror(errno);
					BOS::Utilities::BOSException e(errorMsg);
					throw e;
				}
			}
			else
			{
				// prepare bitmap data content in memory (row+padding)*height
				std::size_t rowUnpadded = width * sizeof(BOS::imageHandling::Pixel);
				std::vector<char> paddingData(padding, 0);

				uint16_t fullWidth = rowUnpadded + padding;

				std::vector<char> bitmapData(fullWidth * height);
				for (uint16_t rowNo = 0; rowNo < height; ++rowNo)
				{
					memcpy(&bitmapData[rowNo*fullWidth], reinterpret_cast<const char *>(&imageData->data()[rowNo * width]), rowUnpadded);
					memcpy(&bitmapData[rowNo*fullWidth + rowUnpadded], paddingData.data(), paddingData.size());
				}

				// write to disk
				saveFile.write(&bitmapData.data()[0], bitmapData.size());
				if (saveFile.fail())
				{
					std::string errorMsg = "BOS::imageHandling::BitmapImage::createImageFile():saveFile.write(data) returned: " + (std::string)strerror(errno);
					BOS::Utilities::BOSException e(errorMsg);
					throw e;
				}
			}

			saveFile.close();
		}

		bos_shared_ptr<BOS::imageHandling::ImageData> BitmapImage::getImageData()
		{
			return m_imageData;
		}

		BitmapImage::BitmapImage(const std::string& imageFilename)
		{
			loadImageFile(imageFilename);
		}

		BitmapImage::BitmapImage() { }
	}
}