#include "FloatingEnemyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <cmath>
#include "Level.h"
#include "AudioComponent.h"
#include "Paths.h"

void FloatingEnemyComponent::Start()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	floatOffset = std::rand();
	targetPosition = transform->Position;

	pAudio = go->AddComponent<AudioComponent>();
	auto audio = pAudio.lock();
	audio->LoadClip(Paths::GetInContentPath("Audio/howie.wav"));

	EnableTick(true);
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

void FloatingEnemyComponent::Hit(int damage /*= 1*/)
{
	EnemyComponent::Hit(damage);

	auto go = GetGameObject().lock();

	auto audio = pAudio.lock();
	audio->Play();

}

