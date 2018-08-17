#include "AssetManager.h"

namespace fl {

	AssetManager* AssetManager::s_Instance = nullptr;

	AssetManager::AssetManager()
	{

	}

	AssetManager::~AssetManager()
	{

	}

	void AssetManager::Init()
	{
		s_Instance = new AssetManager();
	}

}