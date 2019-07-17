#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Paths.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include "RenderRule.h"

Level::Level(std::string path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		// load data from file
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string data = buffer.str();

		// split map and object data
		size_t splitIndex = data.find('!');
		std::string mapData = data.substr(0, splitIndex);
		std::string objData = data.substr(splitIndex + 1);

		// iterate over tiles and create objects
		std::istringstream mapStream(mapData);
		std::string mapRow;
		float x = 0;
		float y = 0;
		while (std::getline(mapStream, mapRow))
		{
			for (size_t i = 0; i < mapRow.size(); ++i) 
			{
				// create object
				std::string objPath = Paths::FindObjectPath(objData, mapRow[i]);
				std::weak_ptr<GameObject> obj = SpawnObjectFromFile(objPath, x, y);

				++x;
			}

			x = 0;
			++y;
		}
	}
	else
	{
		std::cout << "Level::Level - Unable to open file " << path << std::endl;
	}
}

std::weak_ptr<GameObject> Level::SpawnObject(std::string name, float x, float y)
{
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	newObjects.push_back(obj);

	obj->Init(name, x, y);

	return obj;
}

std::weak_ptr<GameObject> Level::SpawnObjectFromFile(std::string path, float overrideX, float overrideY)
{
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	newObjects.push_back(obj);

	obj->InitFromFile(path, overrideX, overrideY);

	return obj;
}

void Level::DestroyObject(std::weak_ptr<GameObject> obj)
{
	destroyedObjects.push_back(obj.lock());
}

void Level::Update(float deltaTime)
{
	// Move new game objects to active list
	if (newObjects.size() > 0)
	{
		activeObjects.reserve(activeObjects.size() + newObjects.size());
		std::move(std::begin(newObjects), std::end(newObjects), std::back_inserter(activeObjects));
		newObjects.clear();
	}
	
	// Start new components
	for(auto& obj : activeObjects)
	{
		if (obj && obj->IsInitialized())
		{
			obj->Update_StartComponents();
		}
	}

	// Update game objects
	for(auto& obj : activeObjects)
	{
		if(obj && obj->IsInitialized())
		{
			obj->Update_TickComponents(deltaTime);
		}
	}

	// Remove components pending deletion
	for (auto& obj : activeObjects)
	{
		if (obj && obj->IsInitialized())
		{
			obj->Update_DestroyComponents();
		}
	}

	// Remove game objects pending deletion
	for (auto& obj : destroyedObjects)
	{
		activeObjects.erase(std::remove(activeObjects.begin(), activeObjects.end(), obj), activeObjects.end());
	}
	destroyedObjects.clear();
}

void Level::GetRenderRules(std::vector<RenderRule>& rules) const
{
	for (const auto& obj : activeObjects)
	{
		obj->AppendRenderRules(rules);
	}
}
