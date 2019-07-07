#pragma once
#include "GameComponent.h"

class TransformComponent : public GameComponent
{
public:
	TransformComponent(int x, int y);

	// VARIABLES
public: 
	int x = 0;
	int y = 0;

};