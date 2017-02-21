#ifndef __BOS_TEST_TEST_BMPHANDLING_CPP__
#define __BOS_TEST_TEST_BMPHANDLING_CPP__

#include <string>
#include <iostream>
#include <conio.h>
#include <exception>

#include "ImageHandling/BitmapImage.hpp"
#include "Utilities/BOSException.hpp"

namespace BOS
{
	namespace Test
	{

		bool bmpHandling() 
		{
			std::cout << "24-bit bitmap image read/write testample (test+example) program\n\n";

			std::string readFile1("../Test_BMPHandling/bmp1.bmp"); // read from this file from disk
			std::string writeFile("../Test_BMPHandling/bmp2.bmp"); // write to this file to disk
			std::string readFile2("../Test_BMPHandling/bmp2.bmp"); // read again above file from disk

			try {
				std::cout << "Read from file " << readFile1 <<" from disk\n";
				BOS::imageHandling::BitmapImage bmpFile1(readFile1);
				std::cout << readFile1 << " was read\n";

				std::cout << "Write to " << writeFile << "to disk\n";
				bmpFile1.saveImageFile(writeFile);
				std::cout << writeFile << " was written\n";

				std::cout << "Create an empty BitmapImage object and read file into it (just to show a different way of instantiation)\n";
				BOS::imageHandling::BitmapImage bmpFile2;
				bmpFile2.loadImageFile(writeFile);
				std::cout << writeFile << " was re-read" << std::endl;

				std::cout << "Compare width and height of file bmpFile1 with those of bmpFile2\n";
				uint16_t width1 = bmpFile1.getImageData()->getWidth();
				uint16_t width2 = bmpFile2.getImageData()->getWidth();
				if (width1 != width2)
				{
					throw "Width of the two files is different";
				}

				uint16_t height1 = bmpFile1.getImageData()->getHeight();
				uint16_t height2 = bmpFile2.getImageData()->getHeight();
				if (height1 != height2)
				{
					throw "Height of the two files is different";
				}
				std::cout << "Width and height of the two files are equal" << std::endl;

				// number of pixels to compare on horizontal and vertical direction
				uint16_t numSteps = 3;
				uint16_t stepW = width1 / numSteps - 1;
				uint16_t stepH = height1 / numSteps - 1;

				std::cout << "Compare pixels from bmpFile1 with pixels from bmpFile2";
				for (uint16_t w = 0; w < width1; w += stepW)
					for (uint16_t h = 0; h < height1; h += stepH)
					{
						if (*bmpFile1.getImageData()->getPixel(w,h) != *bmpFile2.getImageData()->getPixel(w,h))
						{ BOS::Utilities::BOSException e("Pixels of the two files differ"); throw e; }
 					}

			} catch (std::exception& e) {
				std::cout << "EXCEPTION: " << e.what() << std::endl;
				return false;
			}
	
			std::cout << "SUCCESS. Pixels of the two files were compared successfully\n";
			return true;
		}

		//int main(int argc, char **argv) {
		//	return (int)BOS::test::bmpHandling();
		//}
	
	}
}

#endif