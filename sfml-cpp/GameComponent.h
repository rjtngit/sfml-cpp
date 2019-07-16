#pragma once
#include "GameComponentLoader.h"
#include <memory>

class GameObject;

class GameComponent
{
	LOADABLE_CLASS_BASE()

public:
	void Init(std::weak_ptr<GameObject> owner);

	// Called when component starts ticking
	virtual void Start() {};

	// Called every frame
	virtual void Tick(float deltaTime) {};

	std::weak_ptr<GameObject> GetGameObject() { return gameObject; }

	// VARIABLES
private:
	std::weak_ptr<GameObject> gameObject;
};
