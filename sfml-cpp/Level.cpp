#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Paths.h"
#include "GameObject.h"
#include <algorithm>

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
		int x = 0;
		int y = 0;
		while (std::getline(mapStream, mapRow))
		{
			for (size_t i = 0; i < mapRow.size(); ++i) 
			{
				// create object
				std::string objPath = Paths::FindObjectPath(objData, mapRow[i]);
				GameObject* obj = SpawnObjectFromFile(objPath, x, y);

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

GameObject* Level::SpawnObject(std::string name, int x, int y)
{
	newObjects.push_back(std::make_unique<GameObject>());
	GameObject* obj = newObjects[newObjects.size() - 1].get();

	obj->Init(name, x, y);

	return obj;
}

GameObject* Level::SpawnObjectFromFile(std::string path, int overrideX, int overrideY)
{
	newObjects.push_back(std::make_unique<GameObject>());
	GameObject* obj = newObjects[newObjects.size() - 1].get();

	obj->InitFromFile(path, overrideX, overrideY);

	return obj;
}

void Level::Update(float deltaTime)
{
	// Remove game objects pending deletion
	for(auto& obj : deletedObjects)
	{
		std::remove(objects.begin(), objects.end(), obj);
	}
	deletedObjects.clear();

	// Move new game objects to active list
	objects.reserve(objects.size() + newObjects.size());
    std::move(std::begin(newObjects), std::end(newObjects), std::back_inserter(objects));
    newObjects.clear();
	
	// Remove components pending deletion
	for(auto& obj : objects)
	{
		obj->DeleteComponents();
	}

	// Start new components
	for(auto& obj : objects)
	{
		obj->StartComponents();
	}

	// Update game objects
	for(auto& obj : objects)
	{
		if(obj->IsInitialized())
		{
			obj->Update(deltaTime);
		}
	}
}
