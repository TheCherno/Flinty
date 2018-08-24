#pragma once

#include "fl/Common.h"
#include "fl/events/Event.h"

namespace fl {

	class FL_API Layer
	{
	public:
		Layer(const std::string& debugName);
		virtual ~Layer();

		virtual void OnTick() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}

		virtual void OnEvent(Event& event) {}
	private:
		std::string m_DebugName;
	};

}