#pragma once

#include "fl/Common.h"

#include "VertexBufferLayout.h"

namespace fl {

	class FL_API VertexBuffer
	{
	public:
		VertexBuffer(const void* buffer, uint size);
		~VertexBuffer();

		void SetLayout(const VertexBufferLayout& layout);

		void Bind() const;
		void Unbind() const;

		inline const VertexBufferLayout& GetLayout() const { return m_Layout; }
	private:
		void Create(const void* buffer);
		void Destroy();
	private:
		uint m_Size;
		uint m_RendererID;
		VertexBufferLayout m_Layout;
	};

}