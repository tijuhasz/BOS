#ifndef __BOS_TEST_TEST_RUNNER_CPP__
#define __BOS_TEST_TEST_RUNNER_CPP__

#include "Test_BMPHandling/Test_BMPHandling.cpp"
#include "Test_ColorBox/Test_ColorBox.cpp"
#include "Test_SchlierenProcessing/Test_SchlierenProcessing.cpp"
#include <stdio.h>

typedef bool (*TestFunction)();

struct TestToRun {
	uint16_t repetition;
	std::string testName;
	uint16_t testId;
	TestFunction function;

	TestToRun(uint16_t repetition_, std::string testName_, TestFunction function_, uint16_t testId_ ): 
				repetition(repetition_), testName(testName_), function(function_), testId(testId_) {}
};

int main(int argc, char **argv)
{
	// Vector of test functions. Set the number of repetitions 
	// to specify how many times to run a test.
	// Set repetition to 0 to skip the test.
	std::vector<TestToRun> testsToRun; 
	testsToRun.push_back(TestToRun(0, "BMPHandling", &BOS::Test::bmpHandling, 0));
	testsToRun.push_back(TestToRun(0, "ColorBox", &BOS::Test::colorBox, 1));
	testsToRun.push_back(TestToRun(1, "SchlierenProcessing", &BOS::Test::schlierenProcessing, 2));

	for(std::vector<TestToRun>::iterator testToRun = testsToRun.begin(); testToRun != testsToRun.end(); ++testToRun) {
		bool result = true;
		for(uint16_t testIteration = 0; testIteration < testToRun->repetition; ++testIteration) {
			std::cout << "\n=============================================================================\n";
			std::cout << "Running test: " << testToRun->testName << ", iteration: " << (testIteration+1) << " of " << testToRun->repetition;
			std::cout << "\n=============================================================================\n";
			result = testToRun->function();
		}
	}
	
	std::cout << "\nPress any key to exit\n"; getch();
}

#endif