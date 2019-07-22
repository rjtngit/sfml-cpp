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

	Vector2 WorldToScreenPoint(Vector2 worldPosition);

	void DrawSprite(std::string texturePath, Vector2 position, RenderPosition renderPos = RenderPosition::WORLD);
	void DrawRect(Vector2 position, Vector2 size, RenderPosition renderPos = RenderPosition::WORLD);

	void SetCameraTarget(Vector2 target) { this->cameraTarget = target; }

private:
	const sf::Texture& GetTexture(std::string path);

	// VARIABLES
private:
	std::shared_ptr<sf::RenderWindow> renderWindow;
	std::map<std::string, sf::Texture> textureCache;
	Vector2 cameraTarget;
};