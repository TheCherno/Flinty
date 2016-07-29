#include <Flinty.h>

#include <iostream>

using namespace fl;

static void OnUpdate()
{
}

static void OnRender(Renderer& renderer)
{
	renderer.SetClearColor(1.0f, 0.0f, 1.0f, 1.0f);
}

int main()
{
	Window window("Sandbox", 1280, 720);
	window.SetUpdateCallback(OnUpdate);
	window.SetRenderCallback(OnRender);
	window.Show();
	return 0;
}