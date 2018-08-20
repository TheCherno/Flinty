#pragma once

#include "fl/assets/Asset.h"

namespace fl {

	class FL_API Framebuffer : public Asset
	{
	public:
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		virtual void Bind(unsigned int slot = 0) const = 0;
		virtual void Unbind() const = 0;
	};

}
