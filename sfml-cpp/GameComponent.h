#pragma once
#include "GameComponentLoader.h"

class GameComponent
{
	LOADABLE_CLASS_BASE()

public:
	virtual void Update(float deltaTime) = 0;

};
