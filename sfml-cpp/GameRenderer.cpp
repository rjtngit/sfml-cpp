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
	sprite.setPosition(position.x, position.y);

	renderWindow->draw(sprite);
}
