#pragma once
#include "EnemyComponent.h"
#include <memory>

class GameObject;

class FloatingEnemyComponent : public EnemyComponent
{
	LOADABLE_CLASS(FloatingEnemyComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;


	// VARIABLES
private:
	Vector2 targetPosition;
	float elapsed = 0.0f;
	float floatStrength = 50.0f;
	int floatOffset = 0;
	float moveSpeed = 100.0f;
};