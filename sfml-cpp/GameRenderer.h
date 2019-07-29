#pragma once
#include <string>
#include "Vector2.h"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "Rect.h"

enum class RenderPosition
{
	WORLD,
	SCREEN
};

class GameRenderer
{
public: 
	GameRenderer(std::shared_ptr<sf::RenderWindow> renderWindow, Vector2 nativeResolution);

	Vector2 WorldToScreenPoint(Vector2 worldPosition) const;

	void DrawSprite(std::string texturePath, Vector2 position, bool flipX, RenderPosition renderPos = RenderPosition::WORLD);
	void DrawSpriteCropped(std::string texturePath, Rect textureCrop, Vector2 position, bool flipX, RenderPosition renderPos = RenderPosition::WORLD);
	void DrawRect(Vector2 position, Vector2 size, RenderPosition renderPos = RenderPosition::WORLD);
	void DrawText(std::string text, std::string fontPath, Vector2 position, RenderPosition renderPos = RenderPosition::SCREEN);

	void SetCameraTarget(Vector2 target) { this->cameraTarget = target; }

private:
	const sf::Texture& GetTexture(std::string path);

	// VARIABLES
private:
	Vector2 nativeResolution;
	std::shared_ptr<sf::RenderWindow> renderWindow;
	std::map<std::string, sf::Texture> textureCache;
	Vector2 cameraTarget;
};