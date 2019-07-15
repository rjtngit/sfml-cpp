#pragma once
#include "GameComponent.h"

class TransformComponent : public GameComponent
{
public:
	TransformComponent(){};
	TransformComponent(int x, int y);
	void Update(float deltaTime) override {};

	// VARIABLES
public: 
	int x = 0;
	int y = 0;
};
