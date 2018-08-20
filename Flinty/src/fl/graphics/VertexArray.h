#pragma once

#include "fl/Common.h"

namespace fl {

	class VertexBuffer;
	class VertexBufferLayout;
	class IndexBuffer;

	class FL_API VertexArray
	{
	public:
		VertexArray();
		VertexArray(VertexBuffer* vb, IndexBuffer* ib);
		~VertexArray();

		void AddVertexBuffer(VertexBuffer* vb);
		void AddIndexBuffer(IndexBuffer* ib);

		void Bind() const;
		void Unbind() const;

		inline VertexBuffer* GetVertexBuffer(uint index = 0) const { return m_VertexBuffers[index]; }
		inline IndexBuffer* GetIndexBuffer(uint index = 0) const { return m_IndexBuffers[index]; }
	private:
		void Create();
		void Destroy();

		void ApplyLayout(const VertexBufferLayout& layout);
	private:
		uint m_RendererID;
		std::vector<VertexBuffer*> m_VertexBuffers;
		std::vector<IndexBuffer*> m_IndexBuffers;
	};

}