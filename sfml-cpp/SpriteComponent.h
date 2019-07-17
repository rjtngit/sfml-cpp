#pragma once
#include "GameComponent.h"
#include <string>

class SpriteComponent : public GameComponent
{
	LOADABLE_CLASS(SpriteComponent)

	void Start() override;
	void Tick(float deltaTime) override;
	const RenderRule Render() override;

	// VARIABLES
public:
	LOADABLE_STRING(spritePath)
	std::string spritePath;

private:
	RenderRule renderRule;
};


