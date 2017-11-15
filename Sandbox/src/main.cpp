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

	uint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	int* pixels = new int[64 * 64];
	for (int i = 0; i < 64 * 64; i++)
		pixels[i] = 0xff0000ff + i * 256;
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

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