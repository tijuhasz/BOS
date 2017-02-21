#include <iostream>
#include "Utilities/ProgressIndicator.hpp";

namespace BOS 
{
	namespace Utilities 
	{
		void ProgressIndicator::progressPercentage(uint16_t percent) {
			std::cout << percent << "%\r";
		}
	}
}