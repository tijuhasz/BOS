#ifndef __BOS_IMAGEHANDLING_PIXEL_HPP__
#define __BOS_IMAGEHANDLING_PIXEL_HPP__

namespace BOS
{
	namespace imageHandling
	{
		// 3-byte (BGR) pixel structure
		#pragma pack(push, 1)
		struct Pixel 
		{
			uint8_t b;
			uint8_t g;
			uint8_t r;

			Pixel& operator =(const Pixel &pxl);
		};
		#pragma pack(pop)

		// Pixel operators
		inline bool operator ==(const Pixel& lhs, const Pixel& rhs)
		{
			if	((lhs.b == rhs.b) &&
				 (lhs.g == rhs.g) &&
				 (lhs.r == rhs.r))
					return true;
			else	return false;
		}

		inline bool operator !=(const Pixel& lhs, const Pixel& rhs)
		{
			if	((lhs.b != rhs.b) ||
				 (lhs.g != rhs.g) ||
				 (lhs.r != rhs.r))
					return true;
			else	return false;
		}

		inline uint32_t operator -(const Pixel& lhs, const Pixel& rhs)
		{
			return  abs(lhs.b - rhs.b) +
					abs(lhs.g - rhs.g) +
					abs(lhs.r - rhs.r);
		}

		inline Pixel& Pixel::operator =(const Pixel& pixel)
		{
			b = pixel.b;
			g = pixel.g;
			r = pixel.r;
			return *this;
		}

	}
}

#endif		
