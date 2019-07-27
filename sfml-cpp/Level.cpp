#include "Level.h"
#include "Paths.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include "RenderRule.h"

Level::Level(std::string path)
	:
	levelData(path)
{
	
}

void Level::LoadData()
{
	const auto layout = levelData.GetLayout();
	for (const LevelData::ObjectData& objData : layout)
	{
		SpawnObjectFromFile(Paths::GetObjectPath(objData.fileName), objData.worldPosition.x, objData.worldPosition.y);
	}
}

std::weak_ptr<GameObject> Level::SpawnObject(std::string name, float x, float y)
{
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	newObjects.push_back(obj);

	obj->Init(shared_from_this(), name, x, y);

	return obj;
}

std::weak_ptr<GameObject> Level::SpawnObjectFromFile(std::string path, float overrideX, float overrideY)
{
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	newObjects.push_back(obj);

	obj->InitFromFile(shared_from_this(), path, overrideX, overrideY);

	return obj;
}

std::weak_ptr<GameObject> Level::SpawnObjectFromFile(std::string path, Vector2 overridePosition)
{
	return SpawnObjectFromFile(path, overridePosition.x, overridePosition.y);
}

void Level::DestroyObject(std::weak_ptr<GameObject> obj)
{
	destroyedObjects.push_back(obj.lock());
}

std::vector<std::weak_ptr<GameObject>> Level::GetObjects()
{
	std::vector<std::weak_ptr<GameObject>> result;

	for (auto& obj : activeObjects)
	{
		result.push_back(obj);
	}

	return result;
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
