#pragma once
#include <string>
#include "Vector2.h"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

enum class RenderPosition
{
	WORLD
};

class GameRenderer
{
public: 
	GameRenderer(std::shared_ptr<sf::RenderWindow> renderWindow);

	void DrawSprite(std::string texturePath, Vector2 position, RenderPosition renderPos = RenderPosition::WORLD);

	void SetCameraTarget(Vector2 target) { this->cameraTarget = target; }

	// VARIABLES
private:
	std::shared_ptr<sf::RenderWindow> renderWindow;
	Vector2 cameraTarget;
};