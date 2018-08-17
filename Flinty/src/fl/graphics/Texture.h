#pragma once

#include "fl/assets/Asset.h"

namespace fl {

	enum class TextureFormat
	{
		None = 0,
		RGB,
		RGBA,
		F16,
		F32
	};

	class FL_API Texture : public Asset
	{
	public:
		virtual int GetWidth() = 0;
		virtual int GetHeight() = 0;
		virtual TextureFormat GetFormat() = 0;

		virtual void Bind(unsigned int slot = 0) = 0;
		virtual void Unbind() = 0;

		static int GetOpenGLFormat(TextureFormat format);
	};

}
