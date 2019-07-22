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
#include "Level.h"


void GameObject::Init(std::weak_ptr<Level> level, std::string name, float x, float y)
{
	this->level = level;

	transform = AddComponent<TransformComponent>();

	auto pTransform = transform.lock();
	pTransform->Position.x = x;
	pTransform->Position.y = y;

	this->name = name;

	initialized = true;
}

void GameObject::Init(std::weak_ptr<Level> level, float x, float y)
{
	Init(level, "GameObject", x, y);
}

void GameObject::InitFromFile(std::weak_ptr<Level> level, std::string path)
{
	this->level = level;

	transform = AddComponent<TransformComponent>();
	auto pTransform = transform.lock();

	std::ifstream file(path);
	if (file.is_open())
	{
		// load data from file
		nlohmann::json jsonData;
		file >> jsonData;

		// load root gameobject
		this->name = jsonData.contains("name") ? jsonData["name"].get<std::string>() : "GameObject";
		if (jsonData.contains("x")) pTransform->Position.x = jsonData["x"].get<float>();
		if (jsonData.contains("y")) pTransform->Position.y = jsonData["y"].get<float>();

		// load components
		for (auto& compData : jsonData["components"])
		{
			std::string className = compData["_class"].get<std::string>();
			std::weak_ptr<GameComponent> comp = AddComponent(className);
			auto pComp = comp.lock();

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
					pComp->_SetString(it.key(), it->get<std::string>());
				}

				if (it->is_number_integer())
				{
					pComp->_SetInt(it.key(), it->get<int>());
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

void GameObject::InitFromFile(std::weak_ptr<Level> level, std::string path, float overrideX, float overrideY)
{
	InitFromFile(level, path);
	
	auto pTransform = transform.lock();
	pTransform->Position.x = overrideX;
	pTransform->Position.y = overrideY;

}

std::weak_ptr<GameComponent> GameObject::AddComponent(std::string className)
{
	std::shared_ptr<GameComponent> comp = GameComponentLoader::CreateNew(className);
	comp->Init(shared_from_this());
	newComponents.push_back(comp);
	return comp;
}

void GameObject::DestroyComponent(std::weak_ptr<GameComponent> component)
{
	destroyedComponents.push_back(component.lock());
}

void GameObject::Update_DestroyComponents()
{
	// Remove components pending deletion
	for(auto& comp : destroyedComponents)
	{
		activeComponents.erase(std::remove(activeComponents.begin(), activeComponents.end(), comp), activeComponents.end());
		newComponents.erase(std::remove(newComponents.begin(), newComponents.end(), comp), newComponents.end());
	}
	destroyedComponents.clear();
}

void GameObject::Update_StartComponents()
{
	// Start and move new components to active list
	int numNew = newComponents.size();
	activeComponents.reserve(activeComponents.size() + numNew);
    std::move(std::begin(newComponents), std::end(newComponents), std::back_inserter(activeComponents));
    newComponents.clear();

	for (size_t i = activeComponents.size() - numNew; i < activeComponents.size(); i++)
	{
		auto comp = activeComponents[i];
		comp->Start();
	}
}

void GameObject::Update_TickComponents(float deltaTime)
{
	// Update components
	for(auto& comp : activeComponents)
	{
		comp->Tick(deltaTime);
	}
}

void GameObject::AppendRenderRules(std::vector<RenderRule>& rules) const
{
	for (const auto& comp : activeComponents)
	{
		rules.push_back(comp->GetRenderRule());
	}
}

