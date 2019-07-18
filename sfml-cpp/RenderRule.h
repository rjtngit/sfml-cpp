#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

class GameComponent;

struct RenderRule
{
public:
	static const RenderRule NoRender;

	bool render = false;
	int order = 0;
	GameComponent* gameComponent = nullptr;
};



