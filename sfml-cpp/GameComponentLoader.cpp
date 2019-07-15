#include "GameComponentLoader.h"

namespace GameComponentLoader
{
	GameComponent* GameComponentLoader::CreateNew(std::string className)
	{
		auto& map = get_map();
		auto it = map.find(className);
		if (it == map.end())
		{
			std::cout << "GameComponentLoader::CreateNew: " << className << " not found. Did you mark it with LOADABLE_CLASS?" << std::endl;
			return nullptr;
		}

		return it->second();
	}

	std::unordered_map<std::string, std::function<GameComponent*()>> & GameComponentLoader::get_map()
	{
		static std::unordered_map<std::string, std::function<GameComponent*()>> map;
		return map;
	}



}

