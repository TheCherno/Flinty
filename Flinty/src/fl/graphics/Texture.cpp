#include "Texture.h"

#include <fl/gl.h>

namespace fl {

	int Texture::GetOpenGLFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB:		return GL_RGB;
		case TextureFormat::RGBA:		return GL_RGBA;
		case TextureFormat::F16:		return GL_RGBA16F;
		case TextureFormat::F32:		return GL_RGBA32F;
		case TextureFormat::Depth:		return GL_DEPTH_COMPONENT;
		case TextureFormat::None:		return 0;
		default:						return 0;
		}
	}

}