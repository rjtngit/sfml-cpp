#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SFML/Window/Keyboard.hpp"
#include <memory>
#include "Level.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"

void PlayerComponent::Start()
{
	auto go = GetGameObject().lock();
	pInput = go->AddComponent<InputComponent>();
}

void PlayerComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();
	auto input = pInput.lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	Vector2 lastPosition = transform->Position;

	// Jumping
	if (input->move_up.GetState())
	{
		if (!isJumping && isGrounded) {
			isJumping = true;
			isGrounded = false;
			velocity.y = -jumpStrength;
		}
	}

	// Movement
	if (input->move_right.GetState())
	{
		if (velocity.x < moveSpeed)
		{
			velocity.x += acceleration * deltaTime;
		}
	}
	else if (input->move_left.GetState())
	{
		if (velocity.x > -moveSpeed)
		{
			velocity.x -= acceleration * deltaTime;
		}
	}
	else
	{
		if (velocity.x > 0)
		{
			velocity.x -= acceleration * deltaTime;
			if (velocity.x < 0)
			{
				velocity.x = 0;
			}
		}
		else if (velocity.x < 0)
		{
			velocity.x += acceleration * deltaTime;
			if (velocity.x > 0)
			{
				velocity.x = 0;
			}
		}
	}

	// Gravity
//	velocity.y += gravity;
	isGrounded = false;

	// Move player
	transform->Position.x += velocity.x * deltaTime;
	transform->Position.y += velocity.y * deltaTime;


	// Collision
	if (collider->IsCollidingAny())
	{
		transform->Position = lastPosition;
		isGrounded = true;
	//	isJumping = false;
	}


	// Update camera
	level->SetCameraTarget(transform->Position);
}


