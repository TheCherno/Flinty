#pragma once

#include <fl/Types.h>

#include "Texture.h"

namespace fl {

	class FL_API Texture2D : public Texture
	{
	public:
		Texture2D(TextureFormat format, int width, int height);
		~Texture2D();

		void SetData(const void* data);

		int GetWidth() override { return m_Width; }
		int GetHeight() override { return m_Height; }
		TextureFormat GetFormat() { return m_Format; }

		void Bind(unsigned int slot = 0);
		void Unbind();
	private:
		void Create();
	private:
		unsigned int m_RendererID;
		int m_Width, m_Height;
		TextureFormat m_Format;
	};

}
