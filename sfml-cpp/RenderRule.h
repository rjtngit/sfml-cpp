#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

class GameComponent;

struct RenderRule
{
public:
	static const RenderRule NoRender;

	bool render = true;
	int order = 0;
	GameComponent* gameComponent = nullptr;
};



