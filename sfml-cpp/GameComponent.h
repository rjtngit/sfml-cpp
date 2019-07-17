#pragma once
#include "GameComponentLoader.h"
#include <memory>
#include "RenderRule.h"

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

	// Set up how this component should be rendered this frame. Called after Update.
	virtual const RenderRule Render() { return RenderRule::NoRender; };

	std::weak_ptr<GameObject> GetGameObject() { return gameObject; }

	// VARIABLES
private:
	std::weak_ptr<GameObject> gameObject;
};
