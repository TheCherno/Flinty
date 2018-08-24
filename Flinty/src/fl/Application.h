#pragma once

#include "fl/Common.h"
#include "fl/graphics/Window.h"

#include "fl/LayerStack.h"
#include "fl/events/ApplicationEvent.h"

namespace fl {

	class FL_API Application
	{
	public:
		Application(const std::string& name);
		virtual ~Application();

		void Start();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		virtual void OnInit() {}

		// OnTick() is called once per second
		virtual void OnTick() {}
		
		// OnUpdate() is called at a fixed time interval, usually 60 times per second
		virtual void OnUpdate() {}

		// OnRender() is called whenever a render is requested, usually at vsync
		virtual void OnRender() {}

		inline const std::string& GetName() const { return m_Name; }

		// TODO: Move these into DisplayDevice class
		inline int GetWidth() { return m_Window->GetWidth(); }
		inline int GetHeight() { return m_Window->GetHeight(); }

		inline LayerStack& GetLayerStack() { return m_LayerStack; }
	private:
		void RunLoop();

		void DispatchEvent(Event& event);

		bool OnTickEvent(AppTickEvent& event);
		bool OnUpdateEvent(AppUpdateEvent& event);
		bool OnRenderEvent(AppRenderEvent& event);
		bool OnWindowClosedEvent(WindowClosedEvent& event);
	private:
		std::unique_ptr<Window> m_Window;
		std::string m_Name;
		bool m_Running;
		float m_FrameTime;
		LayerStack m_LayerStack;
	};

}
