#include "GameComponent.h"
#include <string>

GameComponent* BaseComponentLoader::CreateNew(std::string className)
{
	return LoaderFuncs[className]();
}

std::map<std::string, std::function<GameComponent*()>> BaseComponentLoader::LoaderFuncs;
