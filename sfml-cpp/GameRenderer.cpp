#include "GameRenderer.h"

GameRenderer::GameRenderer(std::shared_ptr<sf::RenderWindow> renderWindow)
	:
	renderWindow(renderWindow)
{

}

void GameRenderer::DrawSprite(std::string texturePath, Vector2 position, RenderPosition renderPos /*= RenderPosition::WORLD*/)
{
	sf::Texture texture;
	texture.loadFromFile(texturePath);

	sf::Sprite sprite;
	sprite.setTexture(texture);
	Vector2 screenPos;
	screenPos.x = position.x - cameraTarget.x + renderWindow->getSize().x / 2.0;
	screenPos.y = position.y - cameraTarget.y + renderWindow->getSize().y / 2.0;
	sprite.setPosition(screenPos.x, screenPos.y);

	renderWindow->draw(sprite);
}
