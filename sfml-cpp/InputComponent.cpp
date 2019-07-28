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

	// keyboard
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		bFireUp = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		bFireDown = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		bFireLeft = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		bFireRight = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		bDash = true;
	}

	// joysticks
	// Hard-coded Xbox One button IDs for now
	for (int i = 0; i < sf::Joystick::Count; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) > deadzone)
			{
				bMoveRight = true;
			}

			if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) < -deadzone)
			{
				bMoveLeft = true;
			}

			if (sf::Joystick::isButtonPressed(i, 0))
			{
				bFireDown = true;
			}

			if (sf::Joystick::isButtonPressed(i, 1))
			{
				bFireRight = true;
			}

			if (sf::Joystick::isButtonPressed(i, 2))
			{
				bFireLeft = true;
			}

			if (sf::Joystick::isButtonPressed(i, 3))
			{
				bFireUp = true;
			}

			if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Z) < -deadzone )
			{
				bDash = true;
			}

			if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::Z) > deadzone)
			{
				bJump = true;
			}

		}
	}


	// Update states
	move_left.Update(bMoveLeft);
	move_right.Update(bMoveRight);
	fire_up.Update(bFireUp);
	fire_down.Update(bFireDown);
	fire_left.Update(bFireLeft);
	fire_right.Update(bFireRight);
	dash.Update(bDash);
	jump.Update(bJump);
}
