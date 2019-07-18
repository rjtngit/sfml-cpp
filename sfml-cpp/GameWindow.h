#pragma once

#include "SFML/Graphics.hpp"
#include "Vector2.h"
#include <string>
#include "Level.h"

class GameRenderer;

class GameWindow
{

public: 
	GameWindow(int width, int height, std::string title);
	void Update();
	void Render(const Level* level);
	bool IsOpen() const;

private:
	std::shared_ptr<sf::RenderWindow> renderWindow;
	GameRenderer renderer;
};