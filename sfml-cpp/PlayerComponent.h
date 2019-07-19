#pragma once
#include "GameComponent.h"

class PlayerComponent : public GameComponent
{
	LOADABLE_CLASS(PlayerComponent)

public:
	void Tick(float deltaTime) override;

	// VARIABLES
public:
	LOADABLE_FLOAT(moveSpeed)
	float moveSpeed = 200.0f;
};

