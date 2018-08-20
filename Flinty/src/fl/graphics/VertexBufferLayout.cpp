#include "VertexBufferLayout.h"

namespace fl {

	VertexBufferLayout::VertexBufferLayout()
		: m_Size(0)
	{
	}

	void VertexBufferLayout::Push(const std::string& name, uint type, uint size, uint count, bool normalized)
	{
		m_Layout.push_back({ name, type, size, count, m_Size, normalized });
		m_Size += size * count;
	}

}