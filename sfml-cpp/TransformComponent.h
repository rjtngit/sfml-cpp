#pragma once
#include "GameComponent.h"

class TransformComponent : public GameComponent
{
public:
	void Update(float deltaTime) override {};

	// VARIABLES
public: 
	int x = 0;
	int y = 0;
};
