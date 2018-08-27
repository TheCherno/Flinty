#include <Flinty.h>

#include <iostream>

#include "fl/debug/ImGuiLayer.h"

#include "SceneLayer.h"

using namespace fl;

class Sandbox : public Application
{
public:
	Sandbox()
		: Application("Sandbox")
	{
		Start();
	}

	void OnInit() override
	{
		PushLayer(new SceneLayer());
		PushOverlay(new debug::ImGuiLayer());
	}
};

int main()
{
	Sandbox sandbox;
}