#pragma once
#include "GameComponent.h"

struct InputState
{
public:
	void Update(bool currentState)
	{
		lastState = state;
		state = currentState;
	}

	bool GetStateDown()
	{
		return state && !lastState;
	}

	bool GetState()
	{
		return state;
	}

	bool GetStateUp()
	{
		return !state && lastState;
	}

private:
	bool lastState = false;
	bool state = false;
};

class InputComponent : public GameComponent
{
public: 
	virtual void Tick(float deltaTime) override;

	// VARIABLES
public:
	const float deadzone = 20.0f;

	InputState move_left;
	InputState move_right;
	InputState fire_up;
	InputState fire_down;
	InputState fire_left;
	InputState fire_right;
	InputState dash;
	InputState jump;


};