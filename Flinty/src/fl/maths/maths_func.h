#pragma once

#include "fl/Common.h"

#include <math.h>

#define FL_PI 3.14159265358f

namespace fl { namespace maths {

	FL_API inline float toRadians(float degrees)
	{
		return (float)(degrees * (FL_PI / 180.0f));
	}

	FL_API inline float toDegrees(float radians)
	{
		return (float)(radians * (180.0f / FL_PI));
	}

	FL_API inline int sign(float value)
	{
		return (value > 0) - (value < 0);
	}

	FL_API inline float sin(float angle)
	{
		return ::sin(angle);
	}

	FL_API inline float cos(float angle)
	{
		return ::cos(angle);
	}

	FL_API inline float tan(float angle)
	{
		return ::tan(angle);
	}

	FL_API inline float sqrt(float value)
	{
		return ::sqrt(value);
	}

	FL_API inline float rsqrt(float value)
	{
		return 1.0f / ::sqrt(value);
	}

	FL_API inline float asin(float value)
	{
		return ::asin(value);
	}

	FL_API inline float acos(float value)
	{
		return ::acos(value);
	}

	FL_API inline float atan(float value)
	{
		return ::atan(value);
	}

	FL_API inline float atan2(float y, float x)
	{
		return ::atan2(y, x);
	}

	FL_API inline float _min(float value, float minimum)
	{
		return (value < minimum) ? minimum : value;
	}

	FL_API inline float _max(float value, float maximum)
	{
		return (value > maximum) ? maximum : value;
	}

	FL_API inline float clamp(float value, float minimum, float maximum)
	{
		return (value > minimum) ? (value < maximum) ? value : maximum : minimum;
	}

} }