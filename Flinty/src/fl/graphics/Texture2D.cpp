#include "Texture2D.h"

#include <fl/gl.h>

namespace fl {

	Texture2D::Texture2D(TextureFormat format, int width, int height)
		: m_RendererID(0), m_Width(width), m_Height(height), m_Format(format)
	{
		Create();
	}

	Texture2D::~Texture2D()
	{

	}

	void Texture2D::Create()
	{
		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		int internalFormat = Texture::GetOpenGLFormat(m_Format);
		int format = Texture::GetOpenGLFormat(m_Format);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, nullptr);
	}

	void Texture2D::SetData(const void* data)
	{
		Bind();
		int format = Texture::GetOpenGLFormat(m_Format);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);
	}

	void Texture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}