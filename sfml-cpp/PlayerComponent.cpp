#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SFML/Window/Keyboard.hpp"
#include <memory>
#include "Level.h"
#include "InputComponent.h"

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

	if (input->move_left.GetState())
	{
		transform->Position.x -= deltaTime * moveSpeed;
	}

	if (input->move_right.GetState())
	{
		transform->Position.x += deltaTime * moveSpeed;
	}

	level->SetCameraTarget(transform->Position);
}


