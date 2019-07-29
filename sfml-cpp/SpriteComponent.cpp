#include "SpriteComponent.h"
#include "GameComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Paths.h"
#include "RenderRule.h"
#include "Rect.h"


void SpriteComponent::Start()
{
	EnableRender(true);
}

RenderRule SpriteComponent::GetRenderRule() 
{
	RenderRule renderRule;
	renderRule.render = visible;
	renderRule.gameComponent = this;
	renderRule.order = renderOrder;

	return renderRule;
}

void SpriteComponent::Render(GameRenderer& target) 
{
	if (cropTexture)
	{
		target.DrawSpriteCropped(Paths::GetInContentPath(spritePath), GetGameObject().lock()->GetTransform().lock()->Position + Vector2(offsetX, offsetY), Rect(cropLeft, cropTop, cropWidth, cropHeight));
	}
	else
	{
		target.DrawSprite(Paths::GetInContentPath(spritePath), GetGameObject().lock()->GetTransform().lock()->Position + Vector2(offsetX, offsetY));
	}
}

