#include "Window.h"

#include <GLFW/glfw3.h>

namespace fl {

	Window::Window(const String& title, uint width, uint height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
	}

	Window::~Window()
	{
	}

	void Window::Show()
	{
		// m_GraphicsThread = std::thread(std::bind(&Window::GraphicsThread, this));
		GraphicsThread();
	}

	void Window::GraphicsThread()
	{
		glfwInit();
		m_GLFWWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		GLFWwindow* window = m_GLFWWindow;

		glfwMakeContextCurrent(window);
		m_Renderer = new Renderer();
		while (!glfwWindowShouldClose(window))
		{
			Clear();
			m_OnUpdate();
			m_OnRender(*m_Renderer);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
	
	void Window::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
