#pragma once

#include <string>
#include "GameObject.h"

class Level 
{
public:
	Level(std::string path);
	GameObject* SpawnObject(int x, int y);

private:
	std::vector<std::unique_ptr<GameObject>> objects;
};