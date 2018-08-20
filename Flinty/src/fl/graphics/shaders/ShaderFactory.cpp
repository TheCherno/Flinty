#include "ShaderFactory.h"

namespace fl { namespace ShaderFactory {

	static const char* s_SimpleShader =
#include "default/Simple.shader"
		;

	static const char* s_FullScreenQuadShader =
#include "default/FullScreenQuad.shader"
		;

	Shader* SimpleShader()
	{
		return Shader::CreateFromSource("Simple Shader", s_SimpleShader);
	}

	Shader* FullScreenQuadShader()
	{
		return Shader::CreateFromSource("FullScreen Quad Shader", s_FullScreenQuadShader);
	}

} }