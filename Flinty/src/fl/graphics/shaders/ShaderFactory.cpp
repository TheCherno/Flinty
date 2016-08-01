#include "ShaderFactory.h"

namespace fl { namespace ShaderFactory {

	static const char* s_SimpleShader =
#include "default/Simple.shader"
		;

	Shader* SimpleShader()
	{
		return Shader::CreateFromSource("Simple Shader", s_SimpleShader);
	}

} }