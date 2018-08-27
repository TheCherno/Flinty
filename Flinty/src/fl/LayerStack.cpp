#include "LayerStack.h"

#include "Layer.h"

namespace fl {

#define LS_BIND_METHOD(method) std::bind(&LayerStack:: ## method, this, std::placeholders::_1)

	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{

	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnInit();
	}

	void LayerStack::PopLayer(Layer* layer)
	{

	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_Overlays.push_back(layer);
		layer->OnInit();
	}

	void LayerStack::PopOverlay(Layer* layer)
	{

	}

	void LayerStack::DispatchEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<AppTickEvent>(LS_BIND_METHOD(OnTickEvent));
		dispatcher.Dispatch<AppUpdateEvent>(LS_BIND_METHOD(OnUpdateEvent));
		dispatcher.Dispatch<AppRenderEvent>(LS_BIND_METHOD(OnRenderEvent));

		OnEvent(event);
	}

	bool LayerStack::OnTickEvent(AppTickEvent& event)
	{
		for (int i = 0; i < m_Overlays.size(); i++)
		{
			Layer* layer = m_Overlays[i];
			layer->OnTick();
		}

		for (int i = 0; i < m_Layers.size(); i++)
		{
			Layer* layer = m_Layers[i];
			layer->OnTick();
		}

		return false;
	}

	bool LayerStack::OnUpdateEvent(AppUpdateEvent& event)
	{
		for (int i = 0; i < m_Overlays.size(); i++)
		{
			Layer* layer = m_Overlays[i];
			layer->OnUpdate();
		}

		for (int i = 0; i < m_Layers.size(); i++)
		{
			Layer* layer = m_Layers[i];
			layer->OnUpdate();
		}

		return false;
	}

	bool LayerStack::OnRenderEvent(AppRenderEvent& event)
	{
		for (int i = 0; i < m_Overlays.size(); i++)
		{
			Layer* layer = m_Overlays[i];
			layer->OnRender();
		}

		for (int i = 0; i < m_Layers.size(); i++)
		{
			Layer* layer = m_Layers[i];
			layer->OnRender();
		}

		return false;
	}

	bool LayerStack::OnEvent(Event& event)
	{
		for (int i = 0; i < m_Overlays.size(); i++)
		{
			Layer* layer = m_Overlays[i];
			layer->OnEvent(event);
		}

		for (int i = 0; i < m_Layers.size(); i++)
		{
			Layer* layer = m_Layers[i];
			layer->OnEvent(event);
		}

		return false;
	}

}