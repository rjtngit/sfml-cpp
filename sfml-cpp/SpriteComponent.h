#pragma once
#include "GameComponent.h"
#include <string>

class SpriteComponent : public GameComponent
{
	LOADABLE_CLASS(SpriteComponent)

public:
	void Start() override;
	RenderRule GetRenderRule() override;
	void Render(GameRenderer& target) override;

	// VARIABLES
public:
	LOADABLE_STRING(name)
	std::string name;

	LOADABLE_STRING(spritePath)
	std::string spritePath;

	LOADABLE_INT(renderOrder)
	int renderOrder = 0;

	LOADABLE_FLOAT(offsetX)
	float offsetX = 0.0f;

	LOADABLE_FLOAT(offsetY)
	float offsetY = 0.0f;

	LOADABLE_FLOAT(anchorX)
	float anchorX = 0;

	LOADABLE_FLOAT(anchorY)
	float anchorY = 0;

	LOADABLE_BOOL(visible)
	bool visible = true;

	LOADABLE_BOOL(flipX)
	bool flipX = false;

	LOADABLE_BOOL(cropTexture)
	bool cropTexture = false;

	LOADABLE_INT(cropTop)
	int cropTop = 0;

	LOADABLE_INT(cropLeft)
	int cropLeft = 0;

	LOADABLE_INT(cropWidth)
	int cropWidth = 0;

	LOADABLE_INT(cropHeight)
	int cropHeight = 0;
};


