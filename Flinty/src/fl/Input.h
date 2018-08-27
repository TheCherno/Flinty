#pragma once

#include "fl/Common.h"
#include "fl/events/Event.h"
#include "fl/math/math.h"

#include <functional>

class GLFWwindow;

namespace fl {

#define MAX_KEYS	1024
#define MAX_BUTTONS	32

	typedef std::function<void(Event& event)> WindowEventCallback;

	class Window;

	class FL_API InputManager
	{
	public:
		InputManager();

		inline void SetEventCallback(const WindowEventCallback& eventCallback) { m_EventCallback = eventCallback; }

		void Update();

		bool IsKeyPressed(uint keycode) const;
		bool IsMouseButtonPressed(uint button) const;
		bool IsMouseButtonClicked(uint button) const;

		const math::vec2& GetMousePosition() const;
		//void SetMousePosition(const math::vec2& position);
		const bool IsMouseGrabbed() const;
		void SetMouseGrabbed(bool grabbed);
		//void SetMouseCursor(int cursor);

		void ClearKeys();
		void ClearMouseButtons();
	private:
		bool m_KeyState[MAX_KEYS];
		bool m_LastKeyState[MAX_KEYS];

		bool m_MouseButtons[MAX_BUTTONS];
		bool m_MouseState[MAX_BUTTONS];
		bool m_MouseClicked[MAX_BUTTONS];
		bool m_MouseGrabbed;
		int m_KeyModifiers;

		math::vec2 m_MousePosition;
		WindowEventCallback m_EventCallback;
	private:
		friend class Window;
		friend void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
		friend void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
		friend void GLFWMousePositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
	};

	class FL_API Input
	{
	public:
		inline static bool IsKeyPressed(uint keycode) { return s_InputManager->IsKeyPressed(keycode); }
		inline static bool IsMouseButtonPressed(uint button) { return s_InputManager->IsMouseButtonPressed(button); }
		inline static bool IsMouseButtonClicked(uint button) { return s_InputManager->IsMouseButtonClicked(button); }

		inline static const math::vec2& GetMousePosition() { return s_InputManager->GetMousePosition(); }

		inline static InputManager* GetInputManager() { return s_InputManager; }
	private:
		friend class InputManager;
	private:
		static InputManager* s_InputManager;
	};

}
