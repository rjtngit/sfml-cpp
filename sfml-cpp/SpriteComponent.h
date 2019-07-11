#pragma once
#include "GameComponent.h"


class SpriteComponent : public GameComponent
{
	
public:
	void Update(float deltaTime) override {};

};


DECLARE_LOADABLE(SpriteComponent);
