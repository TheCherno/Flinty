#include "ShaderUniform.h"

#include "Shader.h"

namespace fl {

	void ShaderStruct::AddField(ShaderUniformDeclaration* field)
	{
		m_Size += field->GetSize();
		uint offset = 0;
		if (m_Fields.size())
		{
			ShaderUniformDeclaration* previous = m_Fields.back();
			offset = previous->GetOffset() + previous->GetSize();
		}
		field->SetOffset(offset);
		m_Fields.push_back(field);
	}


	ShaderUniformDeclaration::ShaderUniformDeclaration(Type type, const String& name, uint count)
		: m_Type(type), m_Struct(nullptr)
	{
		m_Name = name;
		m_Count = count;
		m_Size = SizeOfUniformType(type) * count;
	}

	ShaderUniformDeclaration::ShaderUniformDeclaration(ShaderStruct* uniformStruct, const String& name, uint count)
		: m_Struct(uniformStruct), m_Type(ShaderUniformDeclaration::Type::STRUCT)
	{
		m_Name = name;
		m_Count = count;
		m_Size = m_Struct->GetSize() * count;
	}

	void ShaderUniformDeclaration::SetOffset(uint offset)
	{
		if (m_Type == ShaderUniformDeclaration::Type::STRUCT)
			m_Struct->SetOffset(offset);

		m_Offset = offset;
	}

	uint ShaderUniformDeclaration::SizeOfUniformType(Type type)
	{
		switch (type)
		{
		case ShaderUniformDeclaration::Type::INT32:		return 4;
		case ShaderUniformDeclaration::Type::FLOAT32:	return 4;
		case ShaderUniformDeclaration::Type::VEC2:		return 4 * 2;
		case ShaderUniformDeclaration::Type::VEC3:		return 4 * 3;
		case ShaderUniformDeclaration::Type::VEC4:		return 4 * 4;
		case ShaderUniformDeclaration::Type::MAT3:		return 4 * 3 * 3;
		case ShaderUniformDeclaration::Type::MAT4:		return 4 * 4 * 4;
		}
		return 0;
	}

	ShaderUniformDeclaration::Type ShaderUniformDeclaration::StringToType(const String& type)
	{
		if (type == "int32")		return Type::INT32;
		if (type == "float")	return Type::FLOAT32;
		if (type == "vec2")		return Type::VEC2;
		if (type == "vec3")		return Type::VEC3;
		if (type == "vec4")		return Type::VEC4;
		if (type == "mat3")		return Type::MAT3;
		if (type == "mat4")		return Type::MAT4;

		return Type::NONE;
	}

	String ShaderUniformDeclaration::TypeToString(Type type)
	{
		switch (type)
		{
		case ShaderUniformDeclaration::Type::INT32:		return "int32";
		case ShaderUniformDeclaration::Type::FLOAT32:		return "float";
		case ShaderUniformDeclaration::Type::VEC2:		return "vec2";
		case ShaderUniformDeclaration::Type::VEC3:		return "vec3";
		case ShaderUniformDeclaration::Type::VEC4:		return "vec4";
		case ShaderUniformDeclaration::Type::MAT3:		return "mat3";
		case ShaderUniformDeclaration::Type::MAT4:		return "mat4";
		}
		return "Invalid Type";
	}

	ShaderUniformBufferDeclaration::ShaderUniformBufferDeclaration(const String& name, uint shaderType)
		: m_Name(name), m_ShaderType(shaderType), m_Size(0), m_Register(0)
	{
	}

	void ShaderUniformBufferDeclaration::PushUniform(ShaderUniformDeclaration* uniform)
	{
		uint offset = 0;
		if (m_Uniforms.size())
		{
			ShaderUniformDeclaration* previous = (ShaderUniformDeclaration*)m_Uniforms.back();
			offset = previous->m_Offset + previous->m_Size;
		}
		uniform->SetOffset(offset);
		m_Size += uniform->GetSize();
		m_Uniforms.push_back(uniform);
	}

	ShaderUniformDeclaration* ShaderUniformBufferDeclaration::FindUniform(const String& name)
	{
		for (ShaderUniformDeclaration* uniform : m_Uniforms)
		{
			if (uniform->GetName() == name)
				return uniform;
		}
		return nullptr;
	}

}