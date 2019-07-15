#pragma once
#include "GameComponent.h"
#include <string>

class SpriteComponent : public GameComponent
{
	LOADABLE_CLASS(SpriteComponent)

public:
	void Update(float deltaTime) override {};

	// VARIABLES
public:
	LOADABLE_STRING(spritePath)
	std::string spritePath;
};


