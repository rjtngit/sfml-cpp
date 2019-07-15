#include "GameObject.h"
#include "TransformComponent.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Paths.h"
#include "json.hpp"
#include <string>
#include <memory>
#include "GameComponent.h"
#include <algorithm>


GameObject::GameObject()
{

}

void GameObject::Init(std::string name, int x, int y)
{
	transform = AddComponent<TransformComponent>();
	transform->x = x;
	transform->y = y;

	initialized = true;
}

void GameObject::Init(int x, int y)
{
	Init("GameObject", x, y);
}

void GameObject::InitFromFile(std::string path)
{
	transform = AddComponent<TransformComponent>();

	std::ifstream file(path);
	if (file.is_open())
	{
		// load data from file
		nlohmann::json jsonData;
		file >> jsonData;

		// load root gameobject
		this->name = jsonData.contains("name") ? jsonData["name"].get<std::string>() : "GameObject";
		if (jsonData.contains("x")) this->transform->x = jsonData["x"].get<int>();
		if (jsonData.contains("y")) this->transform->y = jsonData["y"].get<int>();

		// load components
		for (auto& compData : jsonData["components"])
		{
			std::string className = compData["_class"].get<std::string>();
			GameComponent* comp = AddComponent(className);

			// init variables
			auto it = compData.begin();
			while (it != compData.end())
			{
				if (it.key() == "_class")
				{
					it++;
					continue;
				}

				if (it->is_string())
				{
					comp->_SetString(it.key(), it->get<std::string>());
				}

				if (it->is_number_integer())
				{
					comp->_SetInt(it.key(), it->get<int>());
				}

				it++;
			}
		}

	}
	else
	{
		std::cout << "GameObject::InitFromFile - Unable to open file " << path << std::endl;
	}

	initialized = true;

}

void GameObject::InitFromFile(std::string path, int overrideX, int overrideY)
{
	InitFromFile(path);

	transform->x = overrideX;
	transform->y = overrideY;

}

GameComponent* GameObject::AddComponent(std::string className)
{
	newComponents.push_back(std::unique_ptr<GameComponent>(GameComponentLoader::CreateNew(className)));
	return newComponents[newComponents.size() - 1].get();
}

void GameObject::DeleteComponents()
{
	// Remove components pending deletion
	for(auto& comp : deletedComponents)
	{
		std::remove(deletedComponents.begin(), deletedComponents.end(), comp);
	}
	deletedComponents.clear();
}

void GameObject::StartComponents()
{
	// Start and move new components to active list
	for(auto& comp : newComponents)
	{
		comp->Start();
	}
	components.reserve(components.size() + newComponents.size());
    std::move(std::begin(newComponents), std::end(newComponents), std::back_inserter(components));
    newComponents.clear();
}

void GameObject::Update(float deltaTime)
{
	// Update components
	for(auto& comp : components)
	{
		comp->Update(deltaTime);
	}
}

