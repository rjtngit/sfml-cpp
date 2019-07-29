#pragma once
#include "GameComponent.h"

class SwordKillBoxComponent : public GameComponent
{
	LOADABLE_CLASS(SwordKillBoxComponent)

public:

	void Start() override;
	void Tick(float deltaTime) override;

	// VARIABLES
public:
	int playerId = 0;

	LOADABLE_FLOAT(delay)
	float delay = 0.0f;

private:
	float elapsed = 0.0f;
};