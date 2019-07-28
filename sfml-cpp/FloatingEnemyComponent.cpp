#include "FloatingEnemyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <cmath>
#include "Level.h"

void FloatingEnemyComponent::Start()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	floatOffset = std::rand();
	targetPosition = transform->Position;
}

void FloatingEnemyComponent::Tick(float deltaTime)
{
	elapsed += deltaTime;

	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	// Move	towards target
	// TODO

	// Float around target point
	transform->Position.x = targetPosition.x;
	transform->Position.y = targetPosition.y + (std::sin(elapsed + floatOffset) * floatStrength);
}

