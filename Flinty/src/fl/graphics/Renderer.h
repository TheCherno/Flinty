#pragma once

#include "fl/Common.h"

namespace fl {

	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class Shader;

	class FL_API Renderer
	{
	public:
		Renderer();
		void Init();

		void SetClearColor(float r, float g, float b, float a);
		void Draw(VertexArray* va, Shader* shader);
		void DrawFullScreenQuad(Shader* shader);
	private:
		VertexArray* m_FullScreenQuadVA;
		uint m_VBO, m_IBO;
	};

}

