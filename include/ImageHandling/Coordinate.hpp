#ifndef __BOS_IMAGEHANDLING_COORDINATE_HPP__
#define __BOS_IMAGEHANDLING_COORDINATE_HPP__

#include "BOS.hpp"

namespace BOS
{
	namespace imageHandling
	{
		// Cartesian coordinate (point)
		class Coordinate {
		public:
			Coordinate(int32_t w_, int32_t h_): w(w_), h(h_) {}
			void setCoord(int32_t w_, int32_t h_) { w = w_; h = h_; return; }
			int32_t getWidth() {return w;}
			int32_t getHeight() {return h;}

			inline Coordinate& Coordinate::operator =(const Coordinate& coord);

			int32_t w;
			int32_t h;
		};

		// Coordinate operators
		inline bool operator ==(const Coordinate& lhs, const Coordinate& rhs)
		{
			if	((lhs.w == rhs.w) &&
				 (lhs.h == rhs.h))
					return true;
			else	return false;
		}

		inline bool operator !=(const Coordinate& lhs, const Coordinate& rhs)
		{
			if	((lhs.w != rhs.w) ||
				 (lhs.h != rhs.h))
					return true;
			else	return false;
		}

		inline Coordinate& Coordinate::operator =(const Coordinate& coord)
		{
			w = coord.w;
			h = coord.h;
			return *this;
		}
		
	}
}

#endif		