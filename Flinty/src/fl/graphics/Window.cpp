#include "Window.h"

#include <GLFW/glfw3.h>
#include "fl/system/Timer.h"

#include "fl/events/ApplicationEvent.h"
#include "fl/events/KeyEvent.h"
#include "fl/events/MouseEvent.h"

namespace fl {

	static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
	static void GLFWMousePositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);

	static void EmptyFunction() {}
	static void EmptyRenderFunction(Renderer&) {}
	static void EmptyKeyCallback(int, int) {}
	static void EmptyResizeCallback(int, int) {}

	Window::Window(const String& title, uint width, uint height)
		: m_Title(title), m_Width(width), m_Height(height), m_FrameTime(0.0f)
	{
		m_OnUpdate = EmptyFunction;
		m_OnRender = EmptyRenderFunction;
		m_KeyCallback = EmptyKeyCallback;
		m_ResizeCallback = EmptyResizeCallback;

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
		glfwSetMouseButtonCallback(window, GLFWMouseButtonCallback);
		glfwSetCursorPosCallback(window, GLFWMousePositionCallback);
		glfwSetWindowSizeCallback(window, GLFWWindowSizeCallback);
		glfwMakeContextCurrent(window);

		m_Renderer = new Renderer();
		m_InputManager = new InputManager();
	}

	void Window::ProcessEvents()
	{
		glfwPollEvents();
		if (glfwWindowShouldClose(m_GLFWWindow))
			DispatchEvent(WindowClosedEvent());
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_GLFWWindow);
	}

	void Window::Destroy()
	{
		glfwTerminate();
	}

	void Window::DispatchEvent(Event& event)
	{
		// Forward event to subscriber
		m_EventCallback(event);
	}

	void Window::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	static void GLFWKeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
		if (action == GLFW_PRESS)
			window->DispatchEvent(KeyPressedEvent(key, 0));
		else if (action == GLFW_REPEAT)
			window->DispatchEvent(KeyPressedEvent(key, 1));
		else if (action == GLFW_RELEASE)
			window->DispatchEvent(KeyReleasedEvent(key));

		window->m_InputManager->m_KeyState[key] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
	}

	static void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
		if (action == GLFW_PRESS)
			window->DispatchEvent(MouseButtonPressedEvent(button, 0));
		else if (action == GLFW_REPEAT)
			window->DispatchEvent(MouseButtonPressedEvent(button, 1));
		else if (action == GLFW_RELEASE)
			window->DispatchEvent(MouseButtonReleasedEvent(button));

		window->m_InputManager->m_MouseButtons[button] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
	}

	static void GLFWMousePositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
		window->DispatchEvent(MouseMovedEvent((float)xpos, (float)ypos, 0, 0));

		window->m_InputManager->m_MousePosition = math::vec2((float)xpos, (float)ypos);
	}

	static void GLFWWindowSizeCallback(GLFWwindow* glfwWindow, int width, int height)
	{
		Window* window = (Window*)glfwGetWindowUserPointer(glfwWindow);
		window->m_ResizeCallback(width, height);
		GLCall(glViewport(0, 0, width, height));
	}
}
