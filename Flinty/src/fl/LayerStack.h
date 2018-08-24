#pragma once

#include "fl/Common.h"

#include "fl/events/Event.h"
#include "fl/events/ApplicationEvent.h"

namespace fl {

	class Layer;

	class FL_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);

		void DispatchEvent(Event& event);
	private:
		bool OnTickEvent(AppTickEvent& event);
		bool OnUpdateEvent(AppUpdateEvent& event);
		bool OnRenderEvent(AppRenderEvent& event);
		bool OnEvent(Event& event);
	private:
		std::vector<Layer*> m_Layers;
		std::vector<Layer*> m_Overlays;
	};

}