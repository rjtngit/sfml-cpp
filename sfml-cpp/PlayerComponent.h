#pragma once
#include "GameComponent.h"
#include <map>
#include <functional>
#include <string>
#include "GameComponentLoader.h"


class PlayerComponent : public GameComponent
{
	
public:
	void Update(float deltaTime) override {};

};

DECLARE_LOADABLE(PlayerComponent);
