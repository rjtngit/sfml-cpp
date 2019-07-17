#pragma once
#include "GameComponent.h"

class PlayerComponent : public GameComponent
{
	LOADABLE_CLASS(PlayerComponent)

public:
	void Tick(float deltaTime) override;

	// VARIABLES
public:
	float moveSpeed = 200.0f;
};

