#pragma once

#include <string>
#include "GameObject.h"

class Level 
{
public:
	Level(std::string path);
	std::shared_ptr<GameObject> SpawnObject(std::string name, int x, int y);
	std::shared_ptr<GameObject> SpawnObjectFromFile(std::string path, int overrideX, int overrideY);
	void DestroyObject(std::shared_ptr<GameObject> obj);

	void Update(float deltaTime);

private:
	std::vector<std::shared_ptr<GameObject>> activeObjects;
	std::vector<std::shared_ptr<GameObject>> newObjects;
	std::vector<std::shared_ptr<GameObject>> destroyedObjects;

};