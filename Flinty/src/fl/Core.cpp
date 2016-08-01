#include "Core.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace fl {

	void FlintyInit()
	{
	}

	inline GLenum GLCheckError()
	{
		return glGetError();
	}

	void GLClearError()
	{
		GLCheckError();
	}

	bool GLLogCall(const char* function, const char* file, int line)
	{
		GLenum error = GLCheckError();
		if (error != GL_NO_ERROR)
		{
			std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file <<  ":" << line << std::endl;
			return false;
		}
		return true;
	}

}