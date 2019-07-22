#pragma once
#include "GameComponentLoader.h"
#include <memory>
#include "RenderRule.h"
#include "GameRenderer.h"

class GameObject;

class GameComponent : public std::enable_shared_from_this<GameComponent>
{
	LOADABLE_CLASS_BASE()

public:
	void Init(std::weak_ptr<GameObject> owner);

	// Called when component starts ticking
	virtual void Start() {};

	// Called every frame
	virtual void Tick(float deltaTime) {};

	// How this component should be rendered this frame. Called before Render.
	virtual RenderRule GetRenderRule() { return RenderRule::NoRender; };

	// Render this object. Called after Update.
	virtual void Render(GameRenderer& target) { };


	std::weak_ptr<GameObject> GetGameObject() { return gameObject; }

	// VARIABLES
private:
	std::weak_ptr<GameObject> gameObject;
};
