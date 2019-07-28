#pragma once
#include "EnemyComponent.h"
#include <memory>
#include "AudioComponent.h"

class GameObject;
class AudioComponent;

class FloatingEnemyComponent : public EnemyComponent
{
	LOADABLE_CLASS(FloatingEnemyComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;
	void Hit(int damage = 1) override;

	// VARIABLES
private:
	std::weak_ptr<AudioComponent> pAudio;

	Vector2 targetPosition;
	float elapsed = 0.0f;
	float floatStrength = 50.0f;
	int floatOffset = 0;
	float moveSpeed = 100.0f;
};