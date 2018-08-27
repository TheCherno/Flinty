#pragma once

#include "fl/Common.h"
#include "fl/String.h"
#include "Renderer.h"
#include "fl/events/Event.h"

#include "fl/Input.h"

#include <functional>
#include <thread>

struct GLFWwindow;

namespace fl {

	typedef std::function<void()> UpdateCallback;
	typedef std::function<void(Renderer&)> RenderCallback;
	typedef std::function<void(int, int)> KeyCallback;
	typedef std::function<void(int, int)> ResizeCallback;
	typedef std::function<void(Event&)> EventCallback;

	class FL_API Window
	{
	private:
		String m_Title;
		uint m_Width, m_Height;
		GLFWwindow* m_GLFWWindow;
		UpdateCallback m_OnUpdate;
		RenderCallback m_OnRender;
		KeyCallback m_KeyCallback;
		EventCallback m_EventCallback;
		ResizeCallback m_ResizeCallback;
		std::thread m_GraphicsThread;
		Renderer* m_Renderer;
		InputManager* m_InputManager;

		float m_FrameTime;
	public:
		Window(const String& title, uint width, uint height);
		~Window();

		void Init();

		void ProcessEvents();
		void SwapBuffers();
		void Destroy();

		inline void SetEventCallback(const EventCallback& callback) { m_EventCallback = callback; }
		inline void SetUpdateCallback(const UpdateCallback& callback) { m_OnUpdate = callback; }
		inline void SetRenderCallback(const RenderCallback& callback) { m_OnRender = callback; }
		inline void SetKeyCallback(const KeyCallback& callback) { m_KeyCallback = callback; }
		inline void SetResizeCallback(const ResizeCallback& callback) { m_ResizeCallback = callback; }

		inline float GetFrameTime() const { return m_FrameTime; }

		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }
	private:
		void Clear();

		void DispatchEvent(Event& event);

		friend void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
		friend void GLFWMouseButtonCallback(GLFWwindow* glfwWindow, int button, int action, int mods);
		friend void GLFWMousePositionCallback(GLFWwindow* glfwWindow, double xpos, double ypos);
	};

#define FL_KEY_RELEASED 0
#define FL_KEY_PRESSED	1
#define FL_KEY_REPEAT	2

#define FL_KEY_SPACE              32
#define FL_KEY_APOSTROPHE         39  /* ' */
#define FL_KEY_COMMA              44  /* , */
#define FL_KEY_MINUS              45  /* - */
#define FL_KEY_PERIOD             46  /* . */
#define FL_KEY_SLASH              47  /* / */
#define FL_KEY_0                  48
#define FL_KEY_1                  49
#define FL_KEY_2                  50
#define FL_KEY_3                  51
#define FL_KEY_4                  52
#define FL_KEY_5                  53
#define FL_KEY_6                  54
#define FL_KEY_7                  55
#define FL_KEY_8                  56
#define FL_KEY_9                  57
#define FL_KEY_SEMICOLON          59  /* ; */
#define FL_KEY_EQUAL              61  /* = */
#define FL_KEY_A                  65
#define FL_KEY_B                  66
#define FL_KEY_C                  67
#define FL_KEY_D                  68
#define FL_KEY_E                  69
#define FL_KEY_F                  70
#define FL_KEY_G                  71
#define FL_KEY_H                  72
#define FL_KEY_I                  73
#define FL_KEY_J                  74
#define FL_KEY_K                  75
#define FL_KEY_L                  76
#define FL_KEY_M                  77
#define FL_KEY_N                  78
#define FL_KEY_O                  79
#define FL_KEY_P                  80
#define FL_KEY_Q                  81
#define FL_KEY_R                  82
#define FL_KEY_S                  83
#define FL_KEY_T                  84
#define FL_KEY_U                  85
#define FL_KEY_V                  86
#define FL_KEY_W                  87
#define FL_KEY_X                  88
#define FL_KEY_Y                  89
#define FL_KEY_Z                  90
#define FL_KEY_LEFT_BRACKET       91  /* [ */
#define FL_KEY_BACKSLASH          92  /* \ */
#define FL_KEY_RIGHT_BRACKET      93  /* ] */
#define FL_KEY_GRAVE_ACCENT       96  /* ` */
#define FL_KEY_WORLD_1            161 /* non-US #1 */
#define FL_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define FL_KEY_ESCAPE             256
#define FL_KEY_ENTER              257
#define FL_KEY_TAB                258
#define FL_KEY_BACKSPACE          259
#define FL_KEY_INSERT             260
#define FL_KEY_DELETE             261
#define FL_KEY_RIGHT              262
#define FL_KEY_LEFT               263
#define FL_KEY_DOWN               264
#define FL_KEY_UP                 265
#define FL_KEY_PAGE_UP            266
#define FL_KEY_PAGE_DOWN          267
#define FL_KEY_HOME               268
#define FL_KEY_END                269
#define FL_KEY_CAPS_LOCK          280
#define FL_KEY_SCROLL_LOCK        281
#define FL_KEY_NUM_LOCK           282
#define FL_KEY_PRINT_SCREEN       283
#define FL_KEY_PAUSE              284
#define FL_KEY_F1                 290
#define FL_KEY_F2                 291
#define FL_KEY_F3                 292
#define FL_KEY_F4                 293
#define FL_KEY_F5                 294
#define FL_KEY_F6                 295
#define FL_KEY_F7                 296
#define FL_KEY_F8                 297
#define FL_KEY_F9                 298
#define FL_KEY_F10                299
#define FL_KEY_F11                300
#define FL_KEY_F12                301
#define FL_KEY_F13                302
#define FL_KEY_F14                303
#define FL_KEY_F15                304
#define FL_KEY_F16                305
#define FL_KEY_F17                306
#define FL_KEY_F18                307
#define FL_KEY_F19                308
#define FL_KEY_F20                309
#define FL_KEY_F21                310
#define FL_KEY_F22                311
#define FL_KEY_F23                312
#define FL_KEY_F24                313
#define FL_KEY_F25                314
#define FL_KEY_KP_0               320
#define FL_KEY_KP_1               321
#define FL_KEY_KP_2               322
#define FL_KEY_KP_3               323
#define FL_KEY_KP_4               324
#define FL_KEY_KP_5               325
#define FL_KEY_KP_6               326
#define FL_KEY_KP_7               327
#define FL_KEY_KP_8               328
#define FL_KEY_KP_9               329
#define FL_KEY_KP_DECIMAL         330
#define FL_KEY_KP_DIVIDE          331
#define FL_KEY_KP_MULTIPLY        332
#define FL_KEY_KP_SUBTRACT        333
#define FL_KEY_KP_ADD             334
#define FL_KEY_KP_ENTER           335
#define FL_KEY_KP_EQUAL           336
#define FL_KEY_LEFT_SHIFT         340
#define FL_KEY_LEFT_CONTROL       341
#define FL_KEY_LEFT_ALT           342
#define FL_KEY_LEFT_SUPER         343
#define FL_KEY_RIGHT_SHIFT        344
#define FL_KEY_RIGHT_CONTROL      345
#define FL_KEY_RIGHT_ALT          346
#define FL_KEY_RIGHT_SUPER        347
#define FL_KEY_MENU               348

#define FL_KEY_LAST               FL_KEY_MENU

}