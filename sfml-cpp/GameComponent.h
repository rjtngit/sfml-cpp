#pragma once
#include "GameComponentLoader.h"

class GameObject;

class GameComponent
{
	LOADABLE_CLASS_BASE()

public:
	void Init(std::shared_ptr<GameObject> owner);

	// Called when component starts ticking
	virtual void Start() {};

	// Called every frame
	virtual void Tick(float deltaTime) {};

	std::shared_ptr<GameObject> GetGameObject() { return gameObject; }

	// VARIABLES
private:
	std::shared_ptr<GameObject> gameObject = nullptr;
};
