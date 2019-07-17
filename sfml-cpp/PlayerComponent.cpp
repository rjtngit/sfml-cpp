#include "PlayerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SFML/Window/Keyboard.hpp"


void PlayerComponent::Tick(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		GetGameObject().lock()->GetTransform().lock()->Position.y -= deltaTime * moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		GetGameObject().lock()->GetTransform().lock()->Position.y += deltaTime * moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		GetGameObject().lock()->GetTransform().lock()->Position.x -= deltaTime * moveSpeed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		GetGameObject().lock()->GetTransform().lock()->Position.x += deltaTime * moveSpeed;
	}
}
