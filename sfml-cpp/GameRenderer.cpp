#include "GameRenderer.h"
#include "SFML/System/Vector2.hpp"

Vector2 GameRenderer::WorldToScreenPoint(Vector2 worldPosition)
{
	return Vector2(
		worldPosition.x - cameraTarget.x + renderWindow->getSize().x / 2.0,
		worldPosition.y - cameraTarget.y + renderWindow->getSize().y / 2.0
	);
}

GameRenderer::GameRenderer(std::shared_ptr<sf::RenderWindow> renderWindow)
	:
	renderWindow(renderWindow)
{

}

void GameRenderer::DrawSprite(std::string texturePath, Vector2 position, RenderPosition renderPos /*= RenderPosition::WORLD*/)
{
	const sf::Texture& texture = GetTexture(texturePath);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	Vector2 screenPos = WorldToScreenPoint(position);
	sprite.setPosition(screenPos.x, screenPos.y);

	renderWindow->draw(sprite);
}

void GameRenderer::DrawRect(Vector2 position, Vector2 size, RenderPosition renderPos /*= RenderPosition::WORLD*/)
{
	sf::RectangleShape rectangle(sf::Vector2f(size.x, size.y));
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(1);
	rectangle.setFillColor(sf::Color::Transparent);

	Vector2 screenPos = WorldToScreenPoint(position);
	rectangle.setPosition(screenPos.x, screenPos.y);

	renderWindow->draw(rectangle);
}

const sf::Texture& GameRenderer::GetTexture(std::string path)
{
	auto it = textureCache.find(path);
	if (it == textureCache.end())
	{
		textureCache[path].loadFromFile(path);
	}

	return textureCache[path];
}
