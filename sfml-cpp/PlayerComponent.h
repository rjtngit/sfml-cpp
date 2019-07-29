#pragma once
#include "GameComponent.h"
#include "InputComponent.h"
#include <memory>

class AudioComponent;

enum class PlayerAnimationId
{
	IDLE,
	RUN,
	ATTACK,
	HIT,
	STUNNED,
	DEATH,
};

class PlayerComponent : public GameComponent
{
	LOADABLE_CLASS(PlayerComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;

	void HitByBullet();
	void HitBySword();
	bool IsFullyStunned() { return stunPerc >= 1.0f; };
	bool IsAttacking() { return attackTimeLeft > 0;  }

private:
	void TickMovement(float deltaTime);
	void TickJumpFall(float deltaTime);
	void TickFire(float deltaTime);
	void TickAttack(float deltaTime);

	void UpdateAnimation();

	// VARIABLES
public:
	LOADABLE_INT(playerId)
	float playerId = 0;

	LOADABLE_FLOAT(moveSpeed)
	float moveSpeed = 500.0f;

	LOADABLE_FLOAT(acceleration)
	float acceleration = 5000.0f;

	LOADABLE_FLOAT(jumpStrength)
	float jumpStrength = 1000.0f;

	LOADABLE_FLOAT(jumpMax)
	float jumpMax = 1000.0f;

	LOADABLE_FLOAT(gravity)
	float gravity = 2000.0f;

private:
	std::weak_ptr<InputComponent> pInput;
	std::weak_ptr<AudioComponent> pAudio_Run;
	std::weak_ptr<AudioComponent> pAudio_Jump;
	std::weak_ptr<AudioComponent> pAudio_Fire;

	Vector2 velocity;
	bool isJumping = false;
	bool isGrounded = false;
	float fireCooldownRemaining = 0.0f;
	float fireOverheatRemaining = 0.0f;
	float attackTimeLeft = 0.0f;
	bool attackLeftDirection = false;
	bool playHit = false;

	float stunPerc = 0.0f;
};

