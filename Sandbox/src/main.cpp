#include <Flinty.h>

#include <iostream>
#include <fl/gl.h>

using namespace fl;

Window* s_Window;
Shader* s_Shader;

static void OnUpdate()
{
}

static void OnRender(Renderer& renderer)
{
	renderer.SetClearColor(1.0f, 0.0f, 1.0f, 1.0f);
}

static void OnKeyEvent(int key, int action)
{
}

int main()
{
	Window window("Sandbox", 1280, 720);
	s_Window = &window;

	window.SetUpdateCallback(OnUpdate);
	window.SetRenderCallback(OnRender);
	window.SetKeyCallback(OnKeyEvent);

	s_Shader = ShaderFactory::SimpleShader();
	ShaderManager::Add(s_Shader);

	window.Show();
	return 0;
}