#include "VertexArray.h"

#include "fl/gl.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace fl {

	VertexArray::VertexArray()
		: m_RendererID(0)
	{
		Create();
	}

	VertexArray::VertexArray(VertexBuffer* vb, IndexBuffer* ib)
	{
		Create();
		AddVertexBuffer(vb);
		AddIndexBuffer(ib);
	}

	VertexArray::~VertexArray()
	{
		Destroy();
	}

	void VertexArray::Create()
	{
		GLCall(glGenVertexArrays(1, &m_RendererID));
	}

	void VertexArray::Destroy()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArray::AddVertexBuffer(VertexBuffer* vb)
	{
		m_VertexBuffers.push_back(vb);

		Bind();
		vb->Bind();

		ApplyLayout(vb->GetLayout());

		Unbind();
		vb->Unbind();
	}

	void VertexArray::AddIndexBuffer(IndexBuffer* ib)
	{
		m_IndexBuffers.push_back(ib);

		Bind();
		ib->Bind();
		Unbind();
		ib->Unbind();
	}

	void VertexArray::ApplyLayout(const VertexBufferLayout& layout)
	{
		const std::vector<VertexBufferElement>& elements = layout.GetLayout();
		for (uint i = 0; i < elements.size(); i++)
		{
			const VertexBufferElement& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)element.offset));
		}
	}

	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}