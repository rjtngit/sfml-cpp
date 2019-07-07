#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Level.h"

class GameInstance
{
public:
	GameInstance();
	void Update();
	void Render();
	bool IsRunning() const;

private:
	std::unique_ptr<Level> activeLevel;
	sf::RenderWindow window;
	sf::Clock deltaClock;
};