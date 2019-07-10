#pragma once
#include <map>
#include <functional>
#include <string>
#include <set>

class GameComponent
{

public:
	virtual ~GameComponent() = default;
	virtual void Update(float deltaTime) = 0;

};

