#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "shaders/Shader.h"

namespace fl {

	Renderer* Renderer::s_Instance = nullptr;

	Renderer::Renderer()
	{
		s_Instance = this;
		Init();
	}

	void Renderer::Init()
	{
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Unable to initialize GLEW!" << std::endl;
			return;
		}

		// Create fullscreen quad
		float vertices[] = {
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 0.0f
		};

		uint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));
		IndexBuffer* ib = new IndexBuffer(indices, 6);

		VertexBufferLayout layout;
		layout.Push<math::vec3>("position");
		layout.Push<math::vec2>("texcoord");
		vb->SetLayout(layout);

		m_FullScreenQuadVA = new VertexArray(vb, ib);
	}

	void Renderer::Clear()
	{
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		GLCall(glClearColor(r, g, b, a));
	}

	void Renderer::Draw(VertexArray* va, Shader* shader)
	{
		shader->Bind();
		va->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, va->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL));
	}

	void Renderer::DrawFullScreenQuad(Shader* shader)
	{
		shader->Bind();

		m_FullScreenQuadVA->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, m_FullScreenQuadVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL));
	}

}