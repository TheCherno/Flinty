#pragma once

#include "fl/Common.h"
#include "fl/maths/maths.h"

// From glew.h
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_2_BYTES                        0x1407
#define GL_3_BYTES                        0x1408
#define GL_4_BYTES                        0x1409
#define GL_DOUBLE                         0x140A

namespace fl {

	struct FL_API VertexBufferElement
	{
		std::string name;
		uint type;
		uint size;
		uint count;
		uint offset;
		bool normalized;
	};

	class FL_API VertexBufferLayout
	{
	public:
		VertexBufferLayout();

		inline const std::vector<VertexBufferElement>& GetLayout() const { return m_Layout; }
		inline uint GetStride() const { return m_Size; }

		template<typename T>
		void Push(const std::string& name, uint count = 1, bool normalized = false)
		{
			FL_ASSERT(false, "Unknown type!");
		}

		template<>
		void Push<float>(const std::string& name, uint count, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(float), count, normalized);
		}

		template<>
		void Push<uint>(const std::string& name, uint count, bool normalized)
		{
			Push(name, GL_UNSIGNED_INT, sizeof(uint), count, normalized);
		}

		template<>
		void Push<byte>(const std::string& name, uint count, bool normalized)
		{
			Push(name, GL_UNSIGNED_BYTE, sizeof(byte), count, normalized);
		}

		template<>
		void Push<maths::vec2>(const std::string& name, uint count, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(float), 2 * count, normalized);
		}

		template<>
		void Push<maths::vec3>(const std::string& name, uint count, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(float), 3 * count, normalized);
		}

		template<>
		void Push<maths::vec4>(const std::string& name, uint count, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(float), 4 * count, normalized);
		}
	private:
		void Push(const std::string& name, uint type, uint size, uint count, bool normalized);
	private:
		uint m_Size;
		std::vector<VertexBufferElement> m_Layout;
	};

}  