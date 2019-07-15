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


GameObject::GameObject()
{

}

void GameObject::Init(std::string name, int x, int y)
{
	transform = AddComponent<TransformComponent>(x, y);

	initialized = true;
}

void GameObject::Init(int x, int y)
{
	Init("GameObject", x, y);
}

void GameObject::InitFromFile(std::string path)
{
	transform = AddComponent<TransformComponent>(0, 0);

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
			std::string className = compData["class"].get<std::string>();
			GameComponent* comp = AddComponent(className);

			// init variables
			auto it = compData.begin();
			while (it != compData.end())
			{
				if (it.key() == "class")
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
	components.push_back(std::unique_ptr<GameComponent>(GameComponentLoader::CreateNew(className)));
	return components[components.size() - 1].get();
}

