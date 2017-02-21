#ifndef __BOS_UTILITIES_BOSEXCEPTION_HPP__
#define __BOS_UTILITIES_BOSEXCEPTION_HPP__

#include <string>
#include <exception>
#include <crtdefs.h>

#define DEBUG_INFO "File: " + std::string(__FILE__) + ":" + std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) + " -> "

namespace BOS {

	namespace Utilities {

		class BOSException: public std::runtime_error {
		public:
			BOSException(const std::string& msg) : std::runtime_error(msg) {};
		};

	}
}

#endif