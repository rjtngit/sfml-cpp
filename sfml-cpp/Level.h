#pragma once

#include <string>
#include "GameObject.h"

class Level 
{
public:
	Level(std::string path);
	GameObject* SpawnObject(std::string name, int x, int y);
	GameObject* SpawnObjectFromFile(std::string path, int overrideX, int overrideY);

private:
	std::vector<std::unique_ptr<GameObject>> objects;
};