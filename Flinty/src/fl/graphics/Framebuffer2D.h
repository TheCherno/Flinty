#pragma once

#include <fl/Types.h>

#include "Framebuffer.h"
#include "Texture2D.h"

#include <vector>

namespace fl {

	class FL_API Framebuffer2D : public Framebuffer
	{
	public:
		Framebuffer2D(int width, int height);
		~Framebuffer2D();

		void AttachColor(Texture2D* texture, uint index = 0);
		void AttachDepth(Texture2D* texture);

		Texture2D* GetColorAttachment(uint index = 0) { return m_ColorAttachments[index]; }
		Texture2D* GetDepthAttachment() { return m_DepthAttachment; }

		int GetWidth() const override { return m_Width; }
		int GetHeight() const override { return m_Height; }

		void Bind(unsigned int slot = 0) const override;
		void Unbind() const override;
	private:
		void Create();
		void Destroy();
	private:
		unsigned int m_RendererID;
		int m_Width, m_Height;
		std::vector<Texture2D*> m_ColorAttachments;
		Texture2D* m_DepthAttachment;
	};

}
