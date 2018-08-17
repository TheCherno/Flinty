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
	renderer.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
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

	AssetManager::Init();

	s_Shader = ShaderFactory::SimpleShader();
	ShaderManager::Add(s_Shader);
	s_Shader->Bind();
	s_Shader->SetUniform("pr_matrix", maths::mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	float vertices[] = {
		-8.5f, -8.5f, 0.0f, 0.0f, 1.0f,
		-8.5f,  8.5f, 0.0f, 0.0f, 0.0f,
		 8.5f,  8.5f, 0.0f, 1.0f, 0.0f,
		 8.5f, -8.5f, 0.0f, 1.0f, 1.0f
	};

	int indices[] = {
		0, 1, 2, 2, 3, 0
	};

	int* pixels = new int[64 * 64];
	for (int i = 0; i < 64 * 64; i++)
		pixels[i] = 0xff0000ff + i * 256;

	Texture2D* texture = AssetManager::CreateTexture<Texture2D>(TextureFormat::RGBA, 64, 64);
	texture->SetData(pixels);
	texture->Bind();

	uint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	uint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float)));

	window.Show();
	return 0;
}