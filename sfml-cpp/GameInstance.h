#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Level.h"
#include "GameConfig.h"

class GameInstance
{
public:
	GameInstance(GameConfig config);
	void Update();
	void Render();
	bool IsRunning() const;

private:
	std::unique_ptr<Level> activeLevel;
	sf::RenderWindow window;
	sf::Clock deltaClock;
};