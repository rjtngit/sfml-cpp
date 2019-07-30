#pragma once
#include "GameComponent.h"

class RestartGameTimerComponent : public GameComponent 
{

public:
	void Start() override;
	void Tick(float deltaTime) override;

private:
	float timeLeft = 5.0f;
};