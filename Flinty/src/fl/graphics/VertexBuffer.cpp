#include "VertexBuffer.h"

#include "fl/gl.h"

namespace fl {

	VertexBuffer::VertexBuffer(const void* buffer, uint size)
		: m_Size(size)
	{
		Create(buffer);
	}

	VertexBuffer::~VertexBuffer()
	{
		Destroy();
	}

	void VertexBuffer::SetLayout(const VertexBufferLayout& layout)
	{
		m_Layout = layout;
	}

	void VertexBuffer::Create(const void* buffer)
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, m_Size, buffer, GL_STATIC_DRAW));
	}

	void VertexBuffer::Destroy()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
}