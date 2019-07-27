#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SFML/Window/Keyboard.hpp"
#include <memory>
#include "Level.h"
#include "InputComponent.h"
#include "BoxColliderComponent.h"
#include "Paths.h"
#include "PlayerBulletComponent.h"
#include "WallComponent.h"

void PlayerComponent::Start()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	pInput = go->AddComponent<InputComponent>();
}

void PlayerComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	// Update character
	TickMovement(deltaTime);
	TickJumpFall(deltaTime);
	TickFire(deltaTime);

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
	if (collider->IsOverlappingComponent<WallComponent>())
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
	if (input->jump.GetStateDown())
	{
		if (!isJumping && isGrounded)
		{
			isJumping = true;
			velocity.y = -jumpStrength;
		}
	}

	// Gravity
	velocity.y += gravity * deltaTime;

	// Apply velocity
	transform->Position.y += velocity.y * deltaTime;

	// Collision handling
	isGrounded = false;
	if (collider->IsOverlappingComponent<WallComponent>())
	{
		if (transform->Position.y >= snapshotPosition.y)
		{
			isGrounded = true;
			isJumping = false;
		}

		transform->Position.y = snapshotPosition.y;
		velocity.y = 0;
	}
}

void PlayerComponent::TickFire(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto input = pInput.lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();
	auto level = go->GetLevel().lock();

	Vector2 fireDirection;
	bool isFiring = false;

	if (input->fire_up.GetState())
	{
		fireDirection.y = -1;
		isFiring = true;
	}
	if (input->fire_down.GetState())
	{
		fireDirection.y = 1;
		isFiring = true;
	}
	if (input->fire_left.GetState())
	{
		fireDirection.x = -1;
		isFiring = true;
	}
	if (input->fire_right.GetState())
	{
		fireDirection.x = 1;
		isFiring = true;
	}

	if (isFiring)
	{
		auto bulletGo = level->SpawnObjectFromFile(Paths::GetObjectPath("PlayerBullet.json"), transform->Position).lock();
		auto bullet = bulletGo->GetComponent<PlayerBulletComponent>().lock();
		bullet->direction = fireDirection;
	}
}

