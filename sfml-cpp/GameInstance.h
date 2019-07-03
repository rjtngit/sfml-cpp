#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class GameInstance
{
public:
	GameInstance();
	void Update();
	void Render();
	bool IsRunning() const;

private:
	sf::RenderWindow window;
	sf::Clock deltaClock;
};