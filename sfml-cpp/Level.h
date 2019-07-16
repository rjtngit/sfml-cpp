#pragma once

#include <string>
#include "GameObject.h"

class Level 
{
public:
	Level(std::string path);
	std::weak_ptr<GameObject> SpawnObject(std::string name, float x, float y);
	std::weak_ptr<GameObject> SpawnObjectFromFile(std::string path, float overrideX, float overrideY);
	void DestroyObject(std::weak_ptr<GameObject> obj);

	void Update(float deltaTime);

private:
	std::vector<std::shared_ptr<GameObject>> activeObjects;
	std::vector<std::shared_ptr<GameObject>> newObjects;
	std::vector<std::shared_ptr<GameObject>> destroyedObjects;

};