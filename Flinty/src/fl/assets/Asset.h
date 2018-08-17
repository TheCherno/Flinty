#pragma once

#include "fl/Common.h"

namespace fl {

	class FL_API Asset
	{
	protected:
		Asset() {}
		virtual ~Asset() {}

		unsigned int GetGUID() { return 0; }
	};


}
