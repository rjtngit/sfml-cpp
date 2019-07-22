#pragma once
#include "GameComponent.h"
#include "SFML/Graphics/Rect.hpp"

class BoxColliderComponent : public GameComponent
{
	LOADABLE_CLASS(BoxColliderComponent)

	void Start() override;
	void Tick(float deltaTime) override;
	RenderRule GetRenderRule() override;
	void Render(GameRenderer& target) override;

public:
	bool IsCollidingAny();

	// VARIABLES
public:
	LOADABLE_FLOAT(width)
	float width = 0.0f;

	LOADABLE_FLOAT(height)
	float height = 0.0f;

	LOADABLE_FLOAT(offsetX)
	float offsetX = 0.0f;

	LOADABLE_FLOAT(offsetY)
	float offsetY = 0.0f;

	bool debugDraw = true;




private:
	sf::FloatRect rect;
};