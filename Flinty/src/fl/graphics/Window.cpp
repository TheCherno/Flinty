#include "Window.h"

#include <GLFW/glfw3.h>

namespace fl {

	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void EmptyFunction() {}
	static void EmptyRenderFunction(Renderer&) {}
	static void EmptyKeyCallback(int, int) {}

	Window::Window(const String& title, uint width, uint height)
		: m_Title(title), m_Width(width), m_Height(height)
	{
		m_OnUpdate = EmptyFunction;
		m_OnRender = EmptyRenderFunction;
		m_KeyCallback = EmptyKeyCallback;

		Init();
	}

	Window::~Window()
	{
	}

	void Window::Init()
	{
		glfwInit();
		m_GLFWWindow = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		GLFWwindow* window = m_GLFWWindow;
		glfwSetWindowUserPointer(window, this);
		glfwSetKeyCallback(window, GLFWKeyCallback);
		glfwMakeContextCurrent(window);
		m_Renderer = new Renderer();
	}

	void Window::Show()
	{
		// m_GraphicsThread = std::thread(std::bind(&Window::GraphicsThread, this));
		GraphicsThread();
	}

	void Window::GraphicsThread()
	{
		GLFWwindow* window = m_GLFWWindow;
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

	static void GLFWKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
		window->m_KeyCallback(key, action);
		if (action == GLFW_PRESS)
			window->m_PressedKeys.insert(key);
		else if (action == GLFW_RELEASE)
			window->m_PressedKeys.erase(key);
	}
}
