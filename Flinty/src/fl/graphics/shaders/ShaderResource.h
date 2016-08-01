#pragma once

#include "fl/Common.h"
#include "fl/String.h"

namespace fl {

	class ShaderResourceDeclaration
	{
	public:
		enum class Type
		{
			NONE, TEXTURE2D, TEXTURECUBE, TEXTURESHADOW
		};
	private:
		friend class Shader;
	private:
		String m_Name;
		uint m_Register;
		uint m_Count;
		Type m_Type;
	public:
		ShaderResourceDeclaration(Type type, const String& name, uint count);

		inline const String& GetName() const { return m_Name; }
		inline uint GetRegister() const { return m_Register; }
		inline uint GetCount() const { return m_Count; }

		inline Type GetType() const { return m_Type; }
	public:
		static Type StringToType(const String& type);
		static String TypeToString(Type type);
	};

	typedef std::vector<ShaderResourceDeclaration*> ShaderResourceList;

}