#include "InputComponent.h"
#include <memory>
#include "GameObject.h"
#include "TransformComponent.h"
#include <iostream>


void InputComponent::Start()
{
	EnableTick(true);
}

void InputComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();

	// Poll input
	bool bMoveLeft = false;
	bool bMoveRight = false;
	bool bFireUp = false;
	bool bFireDown = false;
	bool bFireLeft = false;
	bool bFireRight = false;
	bool bDash = false;
	bool bJump = false;

	if (playerId == 0)
	{
		// keyboard (p1)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			bJump = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			bMoveLeft = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			bMoveRight = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			bFireUp = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
		{
			bFireDown = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
		{
			bFireLeft = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			bFireRight = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			bDash = true;
		}
	}
	else
	{
		// keyboard (p2)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			bJump = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			bMoveLeft = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			bMoveRight = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			bFireUp = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		{
			bFireDown = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			bFireLeft = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		{
			bFireRight = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
		{
			bDash = true;
		}
	}
	
	// joysticks
	// Hard-coded Xbox One button IDs for now
	if (sf::Joystick::isConnected(playerId))
	{
		if (sf::Joystick::getAxisPosition(playerId, sf::Joystick::Axis::X) > deadzone)
		{
			bMoveRight = true;
		}

		if (sf::Joystick::getAxisPosition(playerId, sf::Joystick::Axis::X) < -deadzone)
		{
			bMoveLeft = true;
		}

		if (sf::Joystick::isButtonPressed(playerId, 0))
		{
			bFireDown = true;
		}

		if (sf::Joystick::isButtonPressed(playerId, 1))
		{
			bFireRight = true;
		}

		if (sf::Joystick::isButtonPressed(playerId, 2))
		{
			bFireLeft = true;
		}

		if (sf::Joystick::isButtonPressed(playerId, 3))
		{
			bFireUp = true;
		}

		if (sf::Joystick::getAxisPosition(playerId, sf::Joystick::Axis::Z) < -deadzone)
		{
			bDash = true;
		}

		if (sf::Joystick::getAxisPosition(playerId, sf::Joystick::Axis::Z) > deadzone)
		{
			bJump = true;
		}

	}

	// Update states
	move_left.Update(bMoveLeft);
	move_right.Update(bMoveRight);
	fire_up.Update(bFireUp);
	fire_down.Update(bFireDown);
	fire_left.Update(bFireLeft);
	fire_right.Update(bFireRight);
	attack.Update(bDash);
	jump.Update(bJump);
}

