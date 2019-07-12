#pragma once
#include "GameComponentLoader.h"

class GameComponent
{
public:
	virtual void Update(float deltaTime) = 0;

};
