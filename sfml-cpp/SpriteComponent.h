#pragma once
#include "GameComponent.h"
#include <string>

class SpriteComponent : public GameComponent
{
	LOADABLE_CLASS(SpriteComponent)

	void Start() override;
	RenderRule GetRenderRule() override;
	void Render(GameRenderer& target) override;

	// VARIABLES
public:
	LOADABLE_STRING(spritePath)
	std::string spritePath;

	LOADABLE_INT(renderOrder)
	int renderOrder;

	LOADABLE_FLOAT(offsetX)
	float offsetX = 0.0f;

	LOADABLE_FLOAT(offsetY)
	float offsetY = 0.0f;
};


