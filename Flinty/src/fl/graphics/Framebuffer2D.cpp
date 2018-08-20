#include "Framebuffer2D.h"

#include <fl/gl.h>

namespace fl {

	Framebuffer2D::Framebuffer2D(int width, int height)
		: m_Width(width), m_Height(height)
	{
		Create();
	}

	Framebuffer2D::~Framebuffer2D()
	{
		Destroy();
	}

	void Framebuffer2D::Create()
	{
		GLCall(glGenFramebuffers(1, &m_RendererID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	}

	void Framebuffer2D::Destroy()
	{
		GLCall(glDeleteFramebuffers(1, &m_RendererID));
	}

	void Framebuffer2D::AttachColor(Texture2D* texture, uint index)
	{
		FL_ASSERT(m_Width == texture->GetWidth() && m_Height == texture->GetHeight());

		if (m_ColorAttachments.size() <= index)
			m_ColorAttachments.resize(index + 1);

		m_ColorAttachments[index] = texture;

		Bind();
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, texture->GetRendererID(), 0));
		Unbind();
	}

	void Framebuffer2D::AttachDepth(Texture2D* texture)
	{
		FL_ASSERT(m_Width == texture->GetWidth() && m_Height == texture->GetHeight());
		FL_ASSERT(texture->GetFormat() == TextureFormat::Depth);

		m_DepthAttachment = texture;

		Bind();
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetRendererID(), 0));
		Unbind();
	}

	void Framebuffer2D::Bind(unsigned int slot) const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));
	}

	void Framebuffer2D::Unbind() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

}