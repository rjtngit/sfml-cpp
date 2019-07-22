#pragma once
#include "GameComponent.h"
#include "InputComponent.h"
#include <memory>

enum class InputAction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	FIRE,
	DASH
};

class PlayerComponent : public GameComponent
{
	LOADABLE_CLASS(PlayerComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;

	// VARIABLES
public:
	LOADABLE_FLOAT(moveSpeed)
	float moveSpeed = 500.0f;

	LOADABLE_FLOAT(acceleration)
	float acceleration = 5000.0f;

	LOADABLE_FLOAT(jumpStrength)
	float jumpStrength = 500.0f;

	LOADABLE_FLOAT(gravity)
	float gravity = 100.0f;

private:
	std::weak_ptr<InputComponent> pInput;

	Vector2 velocity;
	bool isJumping = false;
	bool isGrounded = false;
};

