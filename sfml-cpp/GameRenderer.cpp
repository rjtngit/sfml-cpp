#include "GameRenderer.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Text.hpp"


GameRenderer::GameRenderer(std::shared_ptr<sf::RenderWindow> renderWindow, Vector2 nativeResolution)
	:
	renderWindow(renderWindow),
	nativeResolution(nativeResolution)
{

}

Vector2 GameRenderer::WorldToScreenPoint(Vector2 worldPosition) const
{
	return Vector2::WorldToScreenPoint(worldPosition, cameraTarget, nativeResolution);
}

void GameRenderer::DrawSprite(std::string texturePath, Vector2 position, bool flipX, RenderPosition renderPos /*= RenderPosition::WORLD*/)
{
	Vector2 screenPos = WorldToScreenPoint(position);
	const sf::Texture& texture = GetTexture(texturePath);

	if (flipX)
	{
		screenPos.x += texture.getSize().x;
	}

	if (screenPos.x < - (int) texture.getSize().x || screenPos.y < -(int) texture.getSize().y || screenPos.x > nativeResolution.x || screenPos.y > nativeResolution.y)
	{
		// cull
		return;
	}

	sf::Sprite sprite;

	sprite.setTexture(texture);

	sprite.setScale(flipX ? -1 : 1, 1);
	sprite.setPosition(screenPos.x, screenPos.y);

	renderWindow->draw(sprite);
}

void GameRenderer::DrawSpriteCropped(std::string texturePath, Rect crop, Vector2 position, bool flipX, RenderPosition renderPos /*= RenderPosition::WORLD*/)
{
	Vector2 screenPos = WorldToScreenPoint(position);
	const sf::Texture& texture = GetTexture(texturePath);

	if (flipX)
	{
		screenPos.x += crop.width;
	}

	if (screenPos.x < -(int)texture.getSize().x || screenPos.y < -(int)texture.getSize().y || screenPos.x > nativeResolution.x || screenPos.y > nativeResolution.y)
	{
		// cull
		return;
	}

	sf::Sprite sprite;

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(crop.left, crop.top, crop.width, crop.height));

	sprite.setPosition(screenPos.x, screenPos.y);
	sprite.setScale(flipX ? -1 : 1, 1);

	renderWindow->draw(sprite);
}

void GameRenderer::DrawRect(Vector2 position, Vector2 size, RenderPosition renderPos /*= RenderPosition::WORLD*/)
{
	Vector2 screenPos = WorldToScreenPoint(position);

	if (screenPos.x < -size.x || screenPos.y < size.y || screenPos.x > nativeResolution.x || screenPos.y > nativeResolution.y)
	{
		// cull
		return;
	}

	sf::RectangleShape rectangle(sf::Vector2f(size.x, size.y));
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(1);
	rectangle.setFillColor(sf::Color::Transparent);

	rectangle.setPosition(screenPos.x, screenPos.y);

	renderWindow->draw(rectangle);
}

void GameRenderer::DrawText(std::string text, std::string fontPath, Vector2 position, RenderPosition renderPos /*= RenderPosition::SCREEN*/)
{
	sf::Font font;
	font.loadFromFile(fontPath);

	sf::Text sftext;
	sftext.setFont(font);
	sftext.setString(text);
	sftext.setFillColor(sf::Color::Red);
	sftext.setPosition(position.x, position.y);

	renderWindow->draw(sftext);
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
