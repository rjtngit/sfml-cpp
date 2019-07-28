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

				if (it->is_number_float())
				{
					pComp->_SetFloat(it.key(), it->get<float>());
				}

				if (it->is_boolean())
				{
					pComp->_SetBool(it.key(), it->get<bool>());
				}

				it++;
			}
		}

	}
	else
	{
		std::cout << "GameObject::InitFromFile - Unable to open file " << path << std::endl;
	}

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
	if (comp)
	{
		comp->Init(shared_from_this());
		components.insert(comp);
	}
	else
	{
		std::cout << "GameObject::AddComponent - Failed to create " << className << std::endl;
	}
	return comp;
}

void GameObject::DestroyComponent(std::weak_ptr<GameComponent> component)
{
	UnregisterForTick(component);
	UnregisterForRender(component);
	UnregisterForStart(component);

	components.erase(component.lock());
}

void GameObject::RegisterForTick(std::weak_ptr<GameComponent> component)
{
	tickComponents.insert(component.lock());

	level.lock()->RegisterForTick(shared_from_this());
}

void GameObject::UnregisterForTick(std::weak_ptr<GameComponent> component)
{
	tickComponents.erase(component.lock());

	if (tickComponents.size() == 0)
	{
		level.lock()->UnregisterForTick(shared_from_this());
	}
}

void GameObject::RegisterForRender(std::weak_ptr<GameComponent> component)
{
	renderComponents.insert(component.lock());

	level.lock()->RegisterForRender(shared_from_this());

}

void GameObject::UnregisterForRender(std::weak_ptr<GameComponent> component)
{
	renderComponents.erase(component.lock());

	if (renderComponents.size() == 0)
	{
		level.lock()->UnregisterForRender(shared_from_this());
	}
}

void GameObject::RegisterForStart(std::weak_ptr<GameComponent> component)
{
	newComponents.insert(component.lock());

	level.lock()->RegisterForStart(shared_from_this());

}

void GameObject::UnregisterForStart(std::weak_ptr<GameComponent> component)
{
	newComponents.erase(component.lock());

	if (newComponents.size() == 0)
	{
		level.lock()->UnregisterForStart(shared_from_this());
	}
}

void GameObject::AppendRenderRules(std::vector<RenderRule>& rules) const
{
	for (const auto& comp : renderComponents)
	{
		if (comp)
		{
			rules.push_back(comp->GetRenderRule());
		}
	}
}


void GameObject::StartComponents()
{
	auto newComponentsCopy = newComponents;
	newComponents.clear();
	for (auto& comp : newComponentsCopy)
	{
		if (comp)
		{
			comp->Start();
		}
	}
}

void GameObject::TickComponents(float deltaTime)
{
	auto tickComponentsCopy = tickComponents;
	for (auto& comp : tickComponentsCopy)
	{
		if (comp)
		{
			comp->Tick(deltaTime);
		}
	}
}

