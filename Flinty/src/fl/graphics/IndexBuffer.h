#pragma once

#include "fl/Common.h"

namespace fl {

	enum class IndexFormat
	{
		None = 0,
		U16,
		U32
	};

	class FL_API IndexBuffer
	{
	public:
		IndexBuffer(unsigned short* indices, uint count);
		IndexBuffer(uint* indices, uint count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline uint GetCount() const { return m_Count; }
		inline IndexFormat GetFormat() const { return m_Format; }
	private:
		void Create(const void* indices);
		void Destroy();

		IndexFormat m_Format;
		uint m_Count;
		uint m_RendererID;
	};

}
