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
#include "AnimatedSpriteComponent.h"
#include "SwordKillBoxComponent.h"
#include "RestartGameTimerComponent.h"



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

	stunPerc -= 0.3f * deltaTime;
	if (stunPerc < 0)
	{
		stunPerc = 0;
	}

	// Poll input / update position
	TickMovement(deltaTime);
	TickJumpFall(deltaTime);
	TickFire(deltaTime);
	TickAttack(deltaTime);

	// Update animation
	UpdateAnimation();
}

void PlayerComponent::HitByBullet()
{
	stunPerc += 0.1f;
	playHit = true;

	if (stunPerc > 1.4f)
	{
		stunPerc = 1.4f;
	}
}

void PlayerComponent::HitBySword()
{
	if (IsFullyStunned())
	{
		auto go = GetGameObject().lock();
		auto transform = go->GetTransform().lock();
		auto level = go->GetLevel().lock();

		level->SpawnObjectFromFile(Paths::GetObjectPath("UI_GameOverLabel.json"));
		auto timerGo = level->SpawnObject("GameRestartTimer", 0,0).lock();
		timerGo->AddComponent<RestartGameTimerComponent>();

		level->DestroyObject(go);
	}
	
}

void PlayerComponent::TickMovement(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto input = pInput.lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	Vector2 snapshotPosition = transform->Position;

	// Get movement input
	if (!IsFullyStunned() && input->move_right.GetState())
	{
		velocity.x += acceleration * deltaTime;
		if (velocity.x > moveSpeed * (1 - stunPerc))
		{
			velocity.x = moveSpeed * (1 - stunPerc);
		}

	}
	else if (!IsFullyStunned() && input->move_left.GetState())
	{
		velocity.x -= acceleration * deltaTime;
		if (velocity.x < -moveSpeed * (1 - stunPerc))
		{
			velocity.x = -moveSpeed * (1 - stunPerc);
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
	if (!IsFullyStunned() && input->jump.GetState())
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
	fireCooldownRemaining -= deltaTime;
	fireOverheatRemaining -= deltaTime;

	if (fireOverheatRemaining <= 0 && !IsFullyStunned() && !IsAttacking())
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
	

	if (isFiring && fireCooldownRemaining <= 0.0f)
	{
		auto bulletGo = level->SpawnObjectFromFile(Paths::GetObjectPath("PlayerBullet.json"), transform->Position).lock();
		auto bullet = bulletGo->GetComponent<PlayerBulletComponent>().lock();
		bullet->direction = fireDirection;
		bullet->playerId = playerId;

		fireCooldownRemaining = 0.1f;

		// Play fire audio
		auto audio = pAudio_Fire.lock();
		audio->Play();
	}

}

void PlayerComponent::TickAttack(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto input = pInput.lock();
	auto level = go->GetLevel().lock();
	auto collider = go->GetComponent<BoxColliderComponent>().lock();

	attackTimeLeft -= deltaTime;

	if (velocity.x != 0 && isGrounded)
	{
		attackLeftDirection = velocity.x < 0;
	}
	
	if (!IsFullyStunned() && input->attack.GetState() && !IsAttacking())
	{
		attackTimeLeft = 0.3f;

		Vector2 killPos = transform->Position;
	
		// hard-coding magic numbers for now because I want to go to sleep
		if (attackLeftDirection)
		{
			killPos.x -= 150;
		}
		else
		{
			killPos.x += 50;
		}
		killPos.y -= 50;

		auto killBoxGo = level->SpawnObjectFromFile(Paths::GetObjectPath("SwordKillBox.json"), killPos).lock();
		auto killBox = killBoxGo->GetComponent<SwordKillBoxComponent>().lock();
		killBox->playerId = playerId;
	}
}

void PlayerComponent::UpdateAnimation()
{
	auto go = GetGameObject().lock();
	auto sprites = go->GetComponents<SpriteComponent>();

	PlayerAnimationId anim = PlayerAnimationId::IDLE;

	
	if (IsFullyStunned())
	{
		anim = PlayerAnimationId::STUNNED;
	}
	else if (IsAttacking())
	{
		anim = PlayerAnimationId::ATTACK;
	}
	else if (playHit)
	{
		playHit = false;
		anim = PlayerAnimationId::HIT;
	}
	else if (isGrounded && velocity.x != 0)
	{
		anim = PlayerAnimationId::RUN;
	}

	for (auto pSprite : sprites)
	{
		auto sprite = pSprite.lock();
		switch (anim)
		{
		case PlayerAnimationId::IDLE:
			sprite->visible = sprite->name == "idle";
			break;
		case PlayerAnimationId::RUN:
			sprite->visible = sprite->name == "run";
			break;
		case PlayerAnimationId::ATTACK:
			if (!sprite->visible)
			{
				auto animSprite = std::dynamic_pointer_cast<AnimatedSpriteComponent>(sprite);
				if (animSprite)
				{
					animSprite->ResetToBeginning();
				}
			}
			sprite->visible = sprite->name == "attack";
			break;
		case PlayerAnimationId::HIT:
			sprite->visible = sprite->name == "hit";
			break;
		case PlayerAnimationId::STUNNED:
			sprite->visible = sprite->name == "stunned";
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
