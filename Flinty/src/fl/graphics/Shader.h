#pragma once

#include "fl/Common.h"

namespace fl {

	class FL_API Shader
	{
	private:

	public:
		Shader(const String& name, const String& path);

		void Bind();
		void Unbind();

		void SetUniform1f(const char* name, float value);
		void SetUniform1i(const char* name, int value);
		void SetUniform2f(const char* name, const maths::vec2& vector);
		void SetUniform3f(const char* name, const maths::vec3& vector);
		void SetUniform4f(const char* name, const maths::vec4& vector);
		void SetUniformMat4(const char* name, const maths::mat4& matrix);
	};

}
