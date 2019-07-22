#pragma once

#include <string>
#include "GameObject.h"
#include "LevelData.h"
#include <memory>

class Level : public std::enable_shared_from_this<Level>
{ 
public:
	Level(std::string path);
	void LoadData();

	std::weak_ptr<GameObject> SpawnObject(std::string name, float x, float y);
	std::weak_ptr<GameObject> SpawnObjectFromFile(std::string path, float overrideX, float overrideY);

	void DestroyObject(std::weak_ptr<GameObject> obj);
	std::vector<std::weak_ptr<GameObject>> GetObjects();

	void Update(float deltaTime);
	void GetRenderRules(std::vector<RenderRule>& rules) const;

	void SetCameraTarget(Vector2 target) { cameraTarget = target;  }
	Vector2 GetCameraTarget() const { return cameraTarget; }


	// VARIABLES
private:
	LevelData levelData;
	Vector2 cameraTarget;

	std::vector<std::shared_ptr<GameObject>> activeObjects;
	std::vector<std::shared_ptr<GameObject>> newObjects;
	std::vector<std::shared_ptr<GameObject>> destroyedObjects;
};