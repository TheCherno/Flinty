#pragma once

#include "fl/Types.h"

namespace fl {

	class FL_API Renderer
	{
	private:

	public:
		Renderer();
		void Init();

		void SetClearColor(float r, float g, float b, float a);
	};

}

