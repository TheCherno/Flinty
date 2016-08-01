#include "ShaderManager.h"

namespace fl {

	HashMap<String, Shader*> ShaderManager::s_Shaders;

	void ShaderManager::Add(Shader* shader)
	{
		s_Shaders[shader->m_Name] = shader;
	}

	Shader* ShaderManager::Get(const String& name)
	{
		if (s_Shaders.find(name) == s_Shaders.end())
			return nullptr;

		return s_Shaders[name];
	}

	void ShaderManager::Clean()
	{
		for (auto i : s_Shaders)
			delete i.second;
	}

	void ShaderManager::Reload(const String& name)
	{
		if (s_Shaders.find(name) == s_Shaders.end())
		{
			std::cout << "Could not find '" << name << "' shader to reload." << std::endl;
			return;
		}

		Shader*& shader = s_Shaders[name];
		String path = shader->GetFilePath();
		String error;
		if (!Shader::TryCompileFromFile(path, error))
		{
			std::cout << error << std::endl;
		}
		else
		{
			shader->~Shader();
			shader = Shader::CreateFromFile(name, path, shader);
			std::cout << "Reloaded shader: " << name << std::endl;
		}
	}

	void ShaderManager::Reload(const Shader* shader)
	{
		String name = shader->GetName();
		String path = shader->GetFilePath();
		shader->~Shader();
		Shader::CreateFromFile(name, path, shader);
	}


}