#ifndef __BOS_UTILITIES_PROGRESSINDICATOR_HPP__
#define __BOS_UTILITIES_PROGRESSINDICATOR_HPP__

#include "BOS.hpp"

namespace BOS {

	namespace Utilities {

		class ProgressIndicator {
		public:
			static void progressPercentage(uint16_t percent);
			static void progressMessage(std::string message);
		};
	}
}

#endif
