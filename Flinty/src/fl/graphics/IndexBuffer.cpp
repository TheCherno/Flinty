#include "IndexBuffer.h"

#include <fl/gl.h>

namespace fl {

	IndexBuffer::IndexBuffer(unsigned short* indices, uint count)
		: m_Format(IndexFormat::U16), m_Count(count), m_RendererID(0)
	{
		Create(indices);
	}

	IndexBuffer::IndexBuffer(uint* indices, uint count)
		: m_Format(IndexFormat::U32), m_Count(count), m_RendererID(0)
	{
		Create(indices);
	}

	IndexBuffer::~IndexBuffer()
	{
		Destroy();
	}

	void IndexBuffer::Create(const void* indices)
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));

		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * (m_Format == IndexFormat::U32 ? 8 : 4), indices, GL_STATIC_DRAW));
	}

	void IndexBuffer::Destroy()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}