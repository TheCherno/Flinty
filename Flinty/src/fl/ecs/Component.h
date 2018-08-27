#pragma once

namespace fl {

	enum class ComponentType
	{
		None = 0,
		MayaCamera
	};

	class Component
	{
	public:
		Component() {}
		virtual ~Component() {}
	protected:
	};
	

}
