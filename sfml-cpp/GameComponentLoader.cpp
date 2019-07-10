#include "GameComponentLoader.h"
#include <iostream>

GameComponent* GameComponentLoader::CreateNew(std::string className)
{
	auto& map = get_map();
	auto it = map.find(className);
	if (it == map.end())
	{
		std::cout << "GameComponentLoader::CreateNew: " << className << " not found. Did you forget to mark it with DECLARE_LOADABLE?" << std::endl;
		return nullptr;
	}

	return it->second();
}

std::map<std::string, std::function<GameComponent*()>> & GameComponentLoader::get_map()
{
	static std::map<std::string, std::function<GameComponent*()>> map;
	return map;
}

