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
	Vector2 position = GetGameObject().lock()->GetTransform().lock()->Position + Vector2(flipX ? -offsetX : offsetX, offsetY);

	if (cropTexture)
	{
		target.DrawSpriteCropped(Paths::GetInContentPath(spritePath), Rect(cropLeft, cropTop, cropWidth, cropHeight), position, flipX, Vector2(anchorX,anchorY));
	}
	else
	{
		target.DrawSprite(Paths::GetInContentPath(spritePath), position, flipX, Vector2(anchorX, anchorY));
	}
}

