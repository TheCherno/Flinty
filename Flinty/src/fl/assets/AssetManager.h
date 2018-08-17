#pragma once

#include "Asset.h"

#include "fl/Common.h"
#include "fl/graphics/Texture2D.h"

namespace fl {
	
	class FL_API AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		// Static API functions
		static void Init();

		template<typename T>
		static T* CreateTexture(TextureFormat format, int width, int height) { FL_ASSERT(s_Instance); return s_Instance->CreateTextureInternal<T>(format, width, height); }
	private:
		// Internal methods
		template<typename T>
		void Create()
		{
			FL_ASSERT(false);
		}

		template<typename T>
		T* CreateTextureInternal(TextureFormat format, int width, int height)
		{
			return new T(format, width, height);
		}
	public:
		static AssetManager* s_Instance;
	};




}
