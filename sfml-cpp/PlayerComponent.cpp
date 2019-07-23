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

	TickMovement(deltaTime);
	TickJumpFall(deltaTime);

	// Update camera
	level->SetCameraTarget(transform->Position);
}

void PlayerComponent::TickMovement(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto input = pInput.lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	Vector2 snapshotPosition = transform->Position;

	// Get movement input
	if (input->move_right.GetState())
	{
		velocity.x += acceleration * deltaTime;
		if (velocity.x > moveSpeed)
		{
			velocity.x = moveSpeed;
		}

	}
	else if (input->move_left.GetState())
	{
		velocity.x -= acceleration * deltaTime;
		if (velocity.x < -moveSpeed)
		{
			velocity.x = -moveSpeed;
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

	// Apply velocity
	transform->Position.x += velocity.x * deltaTime;

	// Handle collision
	auto collisions = collider->GetOverlappingColliders();
	if (collisions.size() > 0)
	{
		transform->Position.x = snapshotPosition.x;
		velocity.x = 0;
	}

}

void PlayerComponent::TickJumpFall(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto input = pInput.lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	Vector2 snapshotPosition = transform->Position;

	// Do jump
	if (input->move_up.GetStateDown())
	{
		if (!isJumping && isGrounded)
		{
			isJumping = true;
			velocity.y = -jumpStrength;
		}
	}
	
	// Apply velocity
	transform->Position.y += velocity.y * deltaTime;

	// Gravity
	velocity.y += gravity * deltaTime;

	// Collision handling
	auto collisions = collider->GetOverlappingColliders();
	if (collisions.size() > 0)
	{
		if (transform->Position.y > snapshotPosition.y)
		{
			isGrounded = true;
			isJumping = false;
		}

		transform->Position.y = snapshotPosition.y;
		velocity.y = 0;
	}

}

