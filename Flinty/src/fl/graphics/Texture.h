#pragma once

#include "fl/assets/Asset.h"

namespace fl {

	enum class TextureFormat
	{
		None = 0,
		RGB,
		RGBA,
		F16,
		F32,
		Depth
	};

	class FL_API Texture : public Asset
	{
	public:
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual TextureFormat GetFormat() const = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;

		virtual uint GetRendererID() const = 0;

		static int GetOpenGLFormat(TextureFormat format);
	};

}
