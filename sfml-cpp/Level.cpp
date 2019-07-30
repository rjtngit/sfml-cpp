#include "Level.h"
#include "Paths.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include "RenderRule.h"

Level::Level(GameInstance* pGameInstance, std::string path)
	:
	pGameInstance(pGameInstance),
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
	obj->Init(shared_from_this(), name, x, y);
	objects.insert(obj);

	return obj;
}

std::weak_ptr<GameObject> Level::SpawnObjectFromFile(std::string path, float overrideX, float overrideY)
{
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	obj->InitFromFile(shared_from_this(), path, overrideX, overrideY);
	objects.insert(obj);

	return obj;
}

std::weak_ptr<GameObject> Level::SpawnObjectFromFile(std::string path, Vector2 overridePosition)
{
	return SpawnObjectFromFile(path, overridePosition.x, overridePosition.y);
}

std::weak_ptr<GameObject> Level::SpawnObjectFromFile(std::string path)
{
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
	obj->InitFromFile(shared_from_this(), path);
	objects.insert(obj);

	return obj;
}

void Level::DestroyObject(std::weak_ptr<GameObject> obj)
{
	UnregisterForTick(obj);
	UnregisterForRender(obj);
	UnregisterForStart(obj);

	objects.erase(obj.lock());
}

std::vector<std::weak_ptr<GameObject>> Level::GetObjects()
{
	std::vector<std::weak_ptr<GameObject>> result;

	for (auto& obj : objects)
	{
		result.push_back(obj);
	}

	return result;
}

void Level::RegisterForTick(std::weak_ptr<GameObject> obj)
{
	tickObjects.insert(obj.lock());
}

void Level::UnregisterForTick(std::weak_ptr<GameObject> obj)
{
	tickObjects.erase(obj.lock());

}

void Level::RegisterForRender(std::weak_ptr<GameObject> obj)
{
	renderObjects.insert(obj.lock());
}

void Level::UnregisterForRender(std::weak_ptr<GameObject> obj)
{
	renderObjects.erase(obj.lock());
}

void Level::RegisterForStart(std::weak_ptr<GameObject> obj)
{
	objectsWithNewComponents.insert(obj.lock());

}

void Level::UnregisterForStart(std::weak_ptr<GameObject> obj)
{
	objectsWithNewComponents.erase(obj.lock());

}

void Level::Update(float deltaTime)
{
	// Start new components
	auto objectsWithNewComponentsCopy = objectsWithNewComponents;
	objectsWithNewComponents.clear();
	for(auto& obj : objectsWithNewComponentsCopy)
	{
		if (obj)
		{
			obj->StartComponents();
		}
	}

	// Update game objects
	auto tickObjectsCopy = tickObjects;
	for(auto& obj : tickObjectsCopy)
	{
		if (obj)
		{
			obj->TickComponents(deltaTime);
		}
	}
}

void Level::GetRenderRules(std::vector<RenderRule>& rules) const
{
	auto renderObjectsCopy = renderObjects;
	for (const auto& obj : renderObjectsCopy)
	{
		if (obj)
		{
			obj->AppendRenderRules(rules);
		}
	}
}
