#pragma once

#include "fl/Common.h"
#include "fl/String.h"

#include <iostream>
#include <vector>

namespace fl {

	class ShaderUniformDeclaration;

	class FL_API ShaderStruct
	{
	private:
		friend class Shader;
	private:
		String m_Name;
		std::vector<ShaderUniformDeclaration*> m_Fields;
		uint m_Size;
		uint m_Offset;
	public:
		ShaderStruct(const String& name)
			: m_Name(name), m_Size(0), m_Offset(0)
		{
		}

		void AddField(ShaderUniformDeclaration* field);

		inline void SetOffset(uint offset) { m_Offset = offset; }

		inline const String& GetName() const { return m_Name; }
		inline uint GetSize() const { return m_Size; }
		inline uint GetOffset() const { return m_Offset; }
		inline const std::vector<ShaderUniformDeclaration*>& GetFields() const { return m_Fields; }
	};

	typedef std::vector<ShaderStruct*> ShaderStructList;

	class FL_API ShaderUniformDeclaration
	{
	private:
		friend class Shader;
		friend class ShaderStruct;
		friend class ShaderUniformBufferDeclaration;
	public:
		enum class Type
		{
			NONE, FLOAT32, VEC2, VEC3, VEC4, MAT3, MAT4, INT32, STRUCT
		};
	private:
		String m_Name;
		uint m_Size;
		uint m_Count;
		uint m_Offset;

		Type m_Type;
		ShaderStruct* m_Struct;
		mutable int m_Location;
	public:
		ShaderUniformDeclaration(Type type, const String& name, uint count = 1);
		ShaderUniformDeclaration(ShaderStruct* uniformStruct, const String& name, uint count = 1);

		inline const String& GetName() const { return m_Name; }
		inline uint GetSize() const { return m_Size; }
		inline uint GetCount() const { return m_Count; }
		inline uint GetOffset() const { return m_Offset; }
		inline uint GetAbsoluteOffset() const { return m_Struct ? m_Struct->GetOffset() + m_Offset : m_Offset; }

		int GetLocation() const { return m_Location; }
		inline Type GetType() const { return m_Type; }
		inline const ShaderStruct& GetShaderUniformStruct() const { FL_ASSERT(m_Struct); return *m_Struct; }
	protected:
		void SetOffset(uint offset);
	public:
		static uint SizeOfUniformType(Type type);
		static Type StringToType(const String& type);
		static String TypeToString(Type type);
	};

	typedef std::vector<ShaderUniformDeclaration*> ShaderUniformList;

	struct FL_API ShaderUniformField
	{
		ShaderUniformDeclaration::Type type;
		String name;
		uint count;
		mutable uint size;
		mutable int location;
	};

	// TODO: Eventually support OpenGL uniform buffers. This is more platform-side.
	class FL_API ShaderUniformBufferDeclaration
	{
	private:
		friend class Shader;
	private:
		String m_Name;
		ShaderUniformList m_Uniforms;
		uint m_Register;
		uint m_Size;
		uint m_ShaderType; // 0 = VS, 1 = PS
	public:
		ShaderUniformBufferDeclaration(const String& name, uint shaderType);

		void PushUniform(ShaderUniformDeclaration* uniform);

		inline const String& GetName() const { return m_Name; }
		inline uint GetRegister() const { return m_Register; }
		inline uint GetShaderType() const { return m_ShaderType; }
		inline uint GetSize() const { return m_Size; }
		inline const ShaderUniformList& GetUniformDeclarations() const { return m_Uniforms; }

		ShaderUniformDeclaration* FindUniform(const String& name);
	};

	typedef std::vector<ShaderUniformBufferDeclaration*> ShaderUniformBufferList;

}
