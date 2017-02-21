#ifndef __BOS_TEST_TEST_SCHLIERENPROCESSING_CPP__
#define __BOS_TEST_TEST_SCHLIERENPROCESSING_CPP__

#include <string>
#include <iostream>
#include <conio.h>
#include <exception>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "ImageHandling/BitmapImage.hpp"
#include "ImageProcessing/Schlieren.hpp"

namespace BOS
{
	namespace Test
	{

		bool schlierenProcessing() 
		{
			std::cout << "BOS Schlieren processing testample (test+example) program\n\n";

			try {

				BOS::imageHandling::BitmapImage referenceFile("../Test_SchlierenProcessing/reference_2968.bmp"); // load file with reference image (to compare other image to it)
				BOS::imageHandling::BitmapImage processFile("../Test_SchlierenProcessing/process_2976.bmp"); // load file with image to be compared with reference image
				std::string resultingImage("../Test_SchlierenProcessing/result.bmp"); // name of file for storing image file result from schlieren processing

				std::cout << "Initialize BOS schlieren processing settings with default settings\n";
				bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> bosSettings = 
				bos_make_shared<BOS::imageProcessing::SchlierenSettings>();
				std::cout << "Set compareAll property of BOS schlieren processing settings to true\n";
				bosSettings->compareAll = false;

				std::cout << "Create BOS processing object\n";
				BOS::imageProcessing::Schlieren bosProcessing(bosSettings);

				std::cout << "Set reference and process image\n";
				bosProcessing.setReferenceImage(referenceFile.getImageData());
				bosProcessing.setProcessImage(processFile.getImageData());

				std::cout << "Generate final image based on reference image and process image\n";
				std::cout << "Progress:\n";

				//boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
				//bosProcessing.generateFinalImage();
				bosProcessing.launchSchlierenProcessingInCpuThreads();
				//boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
				//boost::posix_time::time_duration elapsed = endTime - startTime;
				//std::cout << "Processing took: " << elapsed.total_seconds() << " seconds\n";

				std::cout << "Create image file from final image\n";
				BOS::imageHandling::BitmapImage::createImageFile(resultingImage, bosProcessing.getFinalImage());

				std::cout << "Change BOS processing settings\n";
				bos_shared_ptr<BOS::imageProcessing::SchlierenSettings> newSettings = bosProcessing.getSettings();
				newSettings->boxH += 1;
				bosProcessing.setSettings(newSettings);

			} catch (std::exception& e) {
				std::cout << "EXCEPTION: " << e.what() << std::endl;
				return false;
			} catch (...) {
				std::cout << "Unknown EXCEPTION " << std::endl;
				return false;
			}
	
			std::cout << "SUCCESS. Schlieren processing performed successfully\n";
			return true;
		}

	}
}

#endif