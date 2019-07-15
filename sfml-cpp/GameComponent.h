#pragma once
#include "GameComponentLoader.h"

class GameComponent
{
	LOADABLE_CLASS_BASE()

public:

	// Called when component starts ticking
	virtual void Start() {};

	// Called every frame
	virtual void Update(float deltaTime) {};

};
