#include "ImGuiLayer.h"

namespace fl { namespace debug {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnUpdate()
	{

	}

	void ImGuiLayer::OnRender()
	{

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		if (event.IsInCategory(EventCategoryInput))
			std::cout << event.GetName() << std::endl;
	}

} }