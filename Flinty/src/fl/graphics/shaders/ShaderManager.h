#pragma once

#include "fl/Common.h"
#include "fl/Types.h"

#include "Shader.h"

namespace fl {

	class FL_API ShaderManager
	{
	private:
		static HashMap<String, Shader*> s_Shaders;
	public:
		static void Add(Shader* shader);
		static Shader* Get(const String& name);
		static void Clean();

		static void Reload(const String& name);
		static void Reload(const Shader* shader);
	private:
		ShaderManager() { }
	};

}