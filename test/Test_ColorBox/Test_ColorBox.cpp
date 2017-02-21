#ifndef __BOS_TEST_TEST_COLORBOX_CPP__
#define __BOS_TEST_TEST_COLORBOX_CPP__

#include <string>
#include <iostream>
#include <conio.h>

#include "ImageHandling/BitmapImage.hpp"
#include "ImageProcessing/ColorBox.hpp"
#include "Utilities/BOSException.hpp"

namespace BOS
{
	namespace Test
	{

		bool colorBox() 
		{
			struct PixelAt {
				uint16_t w;
				uint16_t h;
				BOS::imageHandling::Pixel p;
			};
			std::vector<PixelAt> PixelsAt;

			std::cout << "Color box testample (test+example) program\n\n";
			std::string colorBoxFile("ColorBox4.bmp"); // write generated color box to this file
			uint16_t colorBoxSize = 13; // size of the square color box (width == height = size) MUST BE AN ODD NUMBER to have a single pixel in the middle (0,0) position
			uint16_t halfSize = colorBoxSize/2;

			PixelAt orange = {0, 0, {255, 0, 0}};
			PixelsAt.push_back(orange);

			try {
				std::cout << "Create a color box manually\n";
				bos_shared_ptr<BOS::imageProcessing::ColorBox> colorBox = bos_make_shared<BOS::imageProcessing::ColorBox>(colorBoxSize);

				std::cout << "Save colorBox image data to file with a static function\n";
				BOS::imageHandling::BitmapImage::createImageFile(colorBoxFile, colorBox->getImageData());

			} catch (BOS::Utilities::BOSException & e) {
				std::cout << "BOS EXCEPTION: " << e.what() << std::endl;
				return false;
			} catch (std::exception& e) {
				std::cout << "OTHER EXCEPTION: " << e.what() << std::endl;
				return false;
			}
			std::cout << "SUCCESS. Schlieren processing performed successfully\n";
			return true;
		}

	}
}

#endif