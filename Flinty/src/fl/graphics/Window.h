#pragma once

#include "fl/Types.h"
#include "Renderer.h"

#include <functional>
#include <thread>

struct GLFWwindow;

namespace fl {

	typedef std::function<void()> UpdateCallback;
	typedef std::function<void(Renderer&)> RenderCallback;

	class FL_API Window
	{
	private:
		String m_Title;
		uint m_Width, m_Height;
		GLFWwindow* m_GLFWWindow;
		UpdateCallback m_OnUpdate;
		RenderCallback m_OnRender;
		std::thread m_GraphicsThread;
		Renderer* m_Renderer;
	public:
		Window(const String& title, uint width, uint height);
		~Window();

		void Show();

		inline void SetUpdateCallback(const UpdateCallback& callback) { m_OnUpdate = callback; }
		inline void SetRenderCallback(const RenderCallback& callback) { m_OnRender = callback; }
	private:
		void GraphicsThread();

		void Clear();
	};


}