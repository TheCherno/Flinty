#pragma once

#include "fl/Common.h"

#include "fl/maths/maths.h"

#include "ShaderUniform.h"
#include "ShaderResource.h"

namespace fl {

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_MASK_UV_INDEX	2
#define SHADER_TID_INDEX		3
#define SHADER_MID_INDEX		4
#define SHADER_COLOR_INDEX		5

#define SHADER_UNIFORM_PROJECTION_MATRIX_NAME	"sys_ProjectionMatrix"
#define SHADER_UNIFORM_VIEW_MATRIX_NAME			"sys_ViewMatrix"
#define SHADER_UNIFORM_MODEL_MATRIX_NAME		"sys_ModelMatrix"

	struct ShaderErrorInfo
	{
		uint shader;
		String message[2];
		uint line[2];
	};

	class FL_API Shader
	{
	public:
		static const Shader* s_CurrentlyBound;
	private:
		friend class Shader;
		friend class ShaderManager;
	private:
		uint m_Handle;
		String m_Name, m_Path;
		String m_Source;
		String m_VertexSource, m_FragmentSource;

		ShaderUniformBufferList m_VSUniformBuffers;
		ShaderUniformBufferList m_PSUniformBuffers;
		ShaderUniformBufferDeclaration* m_VSUserUniformBuffer;
		ShaderUniformBufferDeclaration* m_PSUserUniformBuffer;
		ShaderResourceList m_Resources;
		ShaderStructList m_Structs;
	public:
		Shader(const String& name, const String& source);
		~Shader();

		void Init();
		void Shutdown();
		void Bind() const;
		void Unbind() const;

		void SetVSSystemUniformBuffer(byte* data, uint size, uint slot);
		void SetPSSystemUniformBuffer(byte* data, uint size, uint slot);

		void SetVSUserUniformBuffer(byte* data, uint size);
		void SetPSUserUniformBuffer(byte* data, uint size);

		void SetUniform(const String& name, byte* data);
		void ResolveAndSetUniformField(const ShaderUniformDeclaration& field, byte* data, int offset);

		inline const String& GetName() const { return m_Name; }
		inline const String& GetFilePath() const { return m_Path; }

		inline const ShaderUniformBufferList& GetVSSystemUniforms() const { return m_VSUniformBuffers; }
		inline const ShaderUniformBufferList& GetPSSystemUniforms() const { return m_PSUniformBuffers; }
		inline const ShaderUniformBufferDeclaration* GetVSUserUniformBuffer() const { return m_VSUserUniformBuffer; }
		inline const ShaderUniformBufferDeclaration* GetPSUserUniformBuffer() const { return m_PSUserUniformBuffer; }
		inline const ShaderResourceList& GetResources() const { return m_Resources; }
	private:
		static uint Compile(String** shaders, ShaderErrorInfo& info = ShaderErrorInfo());
		static void PreProcess(const String& source, String** shaders);

		void Parse(const String& vertexSource, const String& fragmentSource);
		void ParseUniform(const String& statement, uint shaderType);
		void ParseUniformStruct(const String& block, uint shaderType);

		bool IsTypeStringResource(const String& type);

		ShaderStruct* FindStruct(const String& name);

		void ResolveUniforms();
		void ValidateUniforms();
		bool IsSystemUniform(ShaderUniformDeclaration* uniform) const;
		int GetUniformLocation(const String& name);

		ShaderUniformDeclaration* FindUniformDeclaration(const String& name, const ShaderUniformBufferDeclaration* buffer);
		ShaderUniformDeclaration* FindUniformDeclaration(const String& name);

		void ResolveAndSetUniforms(ShaderUniformBufferDeclaration* buffer, byte* data, uint size);
		void ResolveAndSetUniform(ShaderUniformDeclaration* uniform, byte* data, uint size);

		void SetUniformStruct(ShaderUniformDeclaration* uniform, byte* data, int offset);

		void SetUniform1f(const String& name, float value);
		void SetUniform1fv(const String& name, float* value, int count);
		void SetUniform1i(const String& name, int value);
		void SetUniform1iv(const String& name, int* value, int count);
		void SetUniform2f(const String& name, const maths::vec2& vector);
		void SetUniform3f(const String& name, const maths::vec3& vector);
		void SetUniform4f(const String& name, const maths::vec4& vector);
		void SetUniformMat4(const String& name, const maths::mat4& matrix);

		void SetUniform1f(uint location, float value);
		void SetUniform1fv(uint location, float* value, int count);
		void SetUniform1i(uint location, int value);
		void SetUniform1iv(uint location, int* value, int count);
		void SetUniform2f(uint location, const maths::vec2& vector);
		void SetUniform3f(uint location, const maths::vec3& vector);
		void SetUniform4f(uint location, const maths::vec4& vector);
		void SetUniformMat4(uint location, const maths::mat4& matrix);
	public:
		static bool TryCompile(const String& source, String& error);
		static bool TryCompileFromFile(const String& filepath, String& error);
	public:
		static Shader* CreateFromFile(const String& name, const String& filepath, const void* address = nullptr); // TODO: Temp, implement properly
		static Shader* CreateFromSource(const String& name, const String& source);
	};

}