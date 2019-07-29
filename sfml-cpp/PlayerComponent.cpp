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
#include "BlockingComponent.h"
#include "AudioComponent.h"
#include "SpriteComponent.h"



void PlayerComponent::Start()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	// Setup input
	pInput = go->AddComponent<InputComponent>();
	pInput.lock()->SetPlayerId(playerId);

	// Load Audio
	pAudio_Run = go->AddComponent<AudioComponent>();
	auto audio_run = pAudio_Run.lock();
	audio_run->LoadClip(Paths::GetInContentPath("Audio/gallop.wav"));

	pAudio_Jump = go->AddComponent<AudioComponent>();
	auto audio_jump = pAudio_Jump.lock();
	audio_jump->LoadClip(Paths::GetInContentPath("Audio/boing.wav"));

	pAudio_Fire = go->AddComponent<AudioComponent>();
	auto audio_fire = pAudio_Fire.lock();
	audio_fire->LoadClip(Paths::GetInContentPath("Audio/pew.wav"));

	EnableTick(true);
}

void PlayerComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	stunTimeLeft -= deltaTime;

	// Poll input / update position
	TickMovement(deltaTime);
	TickJumpFall(deltaTime);
	TickFire(deltaTime);

	// Update animation
	UpdateAnimation(isGrounded && velocity.x != 0 ? PlayerAnimationId::RUN : PlayerAnimationId::IDLE);
}

void PlayerComponent::Hit()
{
	stunTimeLeft = 0.8f;
}



void PlayerComponent::TickMovement(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto input = pInput.lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	Vector2 snapshotPosition = transform->Position;

	// Get movement input
	if (!IsStunned() && input->move_right.GetState())
	{
		velocity.x += acceleration * deltaTime;
		if (velocity.x > moveSpeed)
		{
			velocity.x = moveSpeed;
		}

	}
	else if (!IsStunned() && input->move_left.GetState())
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
	if (collider->IsOverlappingComponent<BlockingComponent>())
	{
		transform->Position.x = snapshotPosition.x;
		velocity.x = 0;
	}


	// Play run audio
	auto audio = pAudio_Run.lock();
	if (velocity.x != 0 && isGrounded)
	{
		if (!audio->IsPlaying())
		{
			audio->Play();
		}
	}
	else
	{
		audio->Stop();
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
	if (!IsStunned() && input->jump.GetState())
	{
		if (!isJumping && isGrounded)
		{
			isJumping = true;
			velocity.y = -jumpStrength;

			// Play jump audio
			auto audio = pAudio_Jump.lock();
			audio->Play();
		}
	}

	// Gravity
	velocity.y += gravity * deltaTime;

	// Apply velocity
	transform->Position.y += velocity.y * deltaTime;

	// Collision handling
	isGrounded = false;
	if (collider->IsOverlappingComponent<BlockingComponent>())
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
	fireCooldown -= deltaTime;

	if (!IsStunned())
	{
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
	}
	

	if (isFiring && fireCooldown <= 0.0f)
	{
		auto bulletGo = level->SpawnObjectFromFile(Paths::GetObjectPath("PlayerBullet.json"), transform->Position).lock();
		auto bullet = bulletGo->GetComponent<PlayerBulletComponent>().lock();
		bullet->direction = fireDirection;
		bullet->playerId = playerId;

		fireCooldown = 1.2f;

		// Play fire audio
		auto audio = pAudio_Fire.lock();
		audio->Play();
	}

}

void PlayerComponent::UpdateAnimation(PlayerAnimationId animId)
{
	auto go = GetGameObject().lock();
	auto sprites = go->GetComponents<SpriteComponent>();

	for (auto pSprite : sprites)
	{
		auto sprite = pSprite.lock();
		switch (animId)
		{
		case PlayerAnimationId::IDLE:
			sprite->visible = sprite->name == "idle";
			break;
		case PlayerAnimationId::RUN:
			sprite->visible = sprite->name == "run";
			break;
		default:
			sprite->visible = false;
			break;
		}

		if (velocity.x != 0 && isGrounded)
		{
			sprite->flipX = velocity.x < 0;
		}
	}
}
