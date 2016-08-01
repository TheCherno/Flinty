#pragma once

#include "fl/Common.h"

#include "vec3.h"

namespace fl { namespace maths {

	struct mat4;

	struct FL_API vec4
	{
		float x, y, z, w;

		vec4() = default;
		vec4(float scalar);
		vec4(float x, float y, float z, float w);
		vec4(const vec3& xyz, float w);

		vec4& Add(const vec4& other);
		vec4& Subtract(const vec4& other);
		vec4& Multiply(const vec4& other);
		vec4& Divide(const vec4& other);

		vec4 Multiply(const mat4& transform) const;

		friend vec4 operator+(vec4 left, const vec4& right);
		friend vec4 operator-(vec4 left, const vec4& right);
		friend vec4 operator*(vec4 left, const vec4& right);
		friend vec4 operator/(vec4 left, const vec4& right);

		bool operator==(const vec4& other);
		bool operator!=(const vec4& other);

		vec4& operator+=(const vec4& other);
		vec4& operator-=(const vec4& other);
		vec4& operator*=(const vec4& other);
		vec4& operator/=(const vec4& other);

		float Dot(const vec4& other);

		friend std::ostream& operator<<(std::ostream& stream, const vec4& vector);
	};

} }