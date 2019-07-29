#pragma once
#include "GameComponent.h"
#include "Vector2.h"

class PlayerBulletComponent : public GameComponent
{
	LOADABLE_CLASS(PlayerBulletComponent);

public:
	void Start() override;
	void Tick(float deltaTime) override;

	// VARIABLES
public:
	LOADABLE_FLOAT(speed)
	float speed = 0.0f;

	Vector2 direction;

private:
	float elapsed = 0.0f;
};