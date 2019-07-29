#pragma once

#include <string>
#include "GameObject.h"
#include "LevelData.h"
#include <memory>
#include <unordered_set>

class GameInstance;

class Level : public std::enable_shared_from_this<Level>
{ 
public:
	Level(const GameInstance* pGameInstance, std::string path);
	void LoadData();

	std::weak_ptr<GameObject> SpawnObject(std::string name, float x, float y);
	std::weak_ptr<GameObject> SpawnObjectFromFile(std::string path);
	std::weak_ptr<GameObject> SpawnObjectFromFile(std::string path, float overrideX, float overrideY);
	std::weak_ptr<GameObject> SpawnObjectFromFile(std::string path, Vector2 overridePosition);

	void DestroyObject(std::weak_ptr<GameObject> obj);
	std::vector<std::weak_ptr<GameObject>> GetObjects();

	void RegisterForTick(std::weak_ptr<GameObject> obj);
	void UnregisterForTick(std::weak_ptr<GameObject> obj);
	void RegisterForRender(std::weak_ptr<GameObject> obj);
	void UnregisterForRender(std::weak_ptr<GameObject> obj);
	void RegisterForStart(std::weak_ptr<GameObject> obj);
	void UnregisterForStart(std::weak_ptr<GameObject> obj);

	void Update(float deltaTime);
	void GetRenderRules(std::vector<RenderRule>& rules) const;

	void SetCameraTarget(Vector2 target) { cameraTarget = target;  }
	Vector2 GetCameraTarget() const { return cameraTarget; }

	const GameInstance* GetGameInstance() const { return pGameInstance; };

	// VARIABLES
private:
	const GameInstance* pGameInstance;

	LevelData levelData;
	Vector2 cameraTarget;

	std::unordered_set<std::shared_ptr<GameObject>> objects;
	std::unordered_set<std::shared_ptr<GameObject>> objectsWithNewComponents;
	std::unordered_set<std::shared_ptr<GameObject>> tickObjects;
	std::unordered_set<std::shared_ptr<GameObject>> renderObjects;


};