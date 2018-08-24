#pragma once

#include "fl/Common.h"
#include "fl/Layer.h"

namespace fl { namespace debug {

	class FL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate() override;
		void OnRender() override;
		void OnEvent(Event& event) override;
	private:

	};

} }
