#include "SpriteComponent.h"
#include "GameComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Paths.h"
#include "RenderRule.h"


void SpriteComponent::Start()
{
	EnableRender(true);
}

RenderRule SpriteComponent::GetRenderRule() 
{
	RenderRule renderRule;
	renderRule.render = true;
	renderRule.gameComponent = this;
	renderRule.order = renderOrder;

	return renderRule;
}

void SpriteComponent::Render(GameRenderer& target) 
{
	target.DrawSprite(Paths::GetInContentPath(spritePath), GetGameObject().lock()->GetTransform().lock()->Position + Vector2(offsetX, offsetY));
}

