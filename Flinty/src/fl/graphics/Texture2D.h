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

		int GetWidth() const override { return m_Width; }
		int GetHeight() const override { return m_Height; }
		TextureFormat GetFormat() const override { return m_Format; }

		void Bind(unsigned int slot = 0) const override;
		void Unbind() const override;

		uint GetRendererID() const { return m_RendererID; }
	private:
		void Create();
	private:
		unsigned int m_RendererID;
		int m_Width, m_Height;
		TextureFormat m_Format;
	};

}
