#include "GameRenderer.h"

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
	Vector2 screenPos;
	screenPos.x = position.x - cameraTarget.x + renderWindow->getSize().x / 2.0;
	screenPos.y = position.y - cameraTarget.y + renderWindow->getSize().y / 2.0;
	sprite.setPosition(screenPos.x, screenPos.y);

	renderWindow->draw(sprite);
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
