#include "SpriteComponent.h"
#include "GameComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Paths.h"
#include "RenderRule.h"


void SpriteComponent::Start()
{

}

void SpriteComponent::Tick(float deltaTime)
{

}

RenderRule SpriteComponent::GetRenderRule() 
{
	RenderRule renderRule;
	renderRule.render = true;
	renderRule.gameComponent = this;

	return renderRule;
}

void SpriteComponent::Render(GameRenderer& target) 
{
	target.DrawSprite(Paths::GetInContentPath(spritePath), GetGameObject().lock()->GetTransform().lock()->Position);
}

