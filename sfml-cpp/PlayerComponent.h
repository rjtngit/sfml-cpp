#pragma once
#include "GameComponent.h"

class PlayerComponent : public GameComponent
{
	LOADABLE_CLASS(PlayerComponent)

public:
	void Update(float deltaTime) override {};
};

