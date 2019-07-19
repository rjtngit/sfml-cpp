#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SFML/Window/Keyboard.hpp"
#include <memory>
#include "Level.h"


void PlayerComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		transform->Position.y -= deltaTime * moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		transform->Position.y += deltaTime * moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		transform->Position.x -= deltaTime * moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		transform->Position.x += deltaTime * moveSpeed;
	}

	level->SetCameraTarget(transform->Position);
}
