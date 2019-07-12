#pragma once
#include "GameComponent.h"


class SpriteComponent : public GameComponent
{
	DECLARE_LOADABLE(SpriteComponent);

public:
	void Update(float deltaTime) override {};

};


