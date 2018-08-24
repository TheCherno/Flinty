#include "Application.h"

#include <functional>

#include "fl/system/Timer.h"
#include "fl/assets/AssetManager.h"

namespace fl {

#define APP_BIND_METHOD(method) std::bind(&Application:: ## method, this, std::placeholders::_1)

	Application::Application(const std::string& name)
		: m_Name(name), m_FrameTime(0.0f), m_Running(true)
	{
		m_Window = std::make_unique<Window>(name, 1280, 720);
		m_Window->SetEventCallback(APP_BIND_METHOD(DispatchEvent));
	}

	Application::~Application()
	{
	}

	void Application::Start()
	{
		AssetManager::Init();

		OnInit();
		RunLoop();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::RunLoop()
	{
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		uint frames = 0;
		uint updates = 0;
		Timer timer;

		while (m_Running)
		{
			float now = timer.ElapsedMillis();

			m_Window->ProcessEvents();

			if (now - updateTimer > updateTick)
			{
				DispatchEvent(AppUpdateEvent());
				updates++;
				updateTimer += updateTick;
			}

			{
				Timer frametime;
				DispatchEvent(AppRenderEvent());
				frames++;
				m_FrameTime = frametime.ElapsedMillis();
			}
			
			m_Window->SwapBuffers();
		}
		m_Window->Destroy();
	}

	bool Application::OnTickEvent(AppTickEvent& event)
	{
		OnTick();
		return false;
	}

	bool Application::OnUpdateEvent(AppUpdateEvent& event)
	{
		OnUpdate();
		return false;
	}

	bool Application::OnRenderEvent(AppRenderEvent& event)
	{
		OnRender();
		return false;
	}

	bool Application::OnWindowClosedEvent(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}

	void Application::DispatchEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<AppTickEvent>(APP_BIND_METHOD(OnTickEvent));
		dispatcher.Dispatch<AppUpdateEvent>(APP_BIND_METHOD(OnUpdateEvent));
		dispatcher.Dispatch<AppRenderEvent>(APP_BIND_METHOD(OnRenderEvent));
		dispatcher.Dispatch<WindowClosedEvent>(APP_BIND_METHOD(OnWindowClosedEvent));

		m_LayerStack.DispatchEvent(event);
	}

}