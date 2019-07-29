#pragma once
#include "GameComponent.h"
#include "SpriteComponent.h"

class AnimatedSpriteComponent : public SpriteComponent
{
	LOADABLE_CLASS(AnimatedSpriteComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;


	// VARIABLES
public:
	// inherited vars
	LOADABLE_STRING(name)
	LOADABLE_STRING(spritePath)
	LOADABLE_INT(renderOrder)
	LOADABLE_FLOAT(offsetX)
	LOADABLE_FLOAT(offsetY)
	LOADABLE_BOOL(visible)

	LOADABLE_INT(rows)
	int rows = 0;

	LOADABLE_INT(cols)
	int cols = 0;

	LOADABLE_INT(texWidth)
	int texWidth = 0;

	LOADABLE_INT(texHeight)
	int texHeight = 0;

	LOADABLE_FLOAT(frameTime)
	float frameTime = 0.0f;

private: 
	int currentRow = 0;
	int currentCol = 0;
	float frameTimeRemaining = 0.0f;
};