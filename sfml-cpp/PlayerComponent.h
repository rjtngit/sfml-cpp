#pragma once
#include "GameComponent.h"

class PlayerComponent : public GameComponent
{
	DECLARE_LOADABLE(PlayerComponent);

public:
	void Update(float deltaTime) override {};
};

