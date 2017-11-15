#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace fl {

	Renderer::Renderer()
	{
		Init();
	}

	void Renderer::Init()
	{
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Unable to initialize GLEW!" << std::endl;
			return;
		}
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		GLCall(glClearColor(r, g, b, a));
	}

}