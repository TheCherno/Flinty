#include "Renderer.h"

#include <GLFW/glfw3.h>

namespace fl {

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

}