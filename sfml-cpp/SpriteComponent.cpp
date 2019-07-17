#include "SpriteComponent.h"
#include "GameComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Paths.h"
#include "RenderRule.h"


void SpriteComponent::Start()
{
	auto spriteData = renderRule.InitData<SpriteRenderData>();

	spriteData->texture.loadFromFile(Paths::GetInContentPath(spritePath));
	spriteData->sprite.setTexture(spriteData->texture);
}

void SpriteComponent::Tick(float deltaTime)
{

}

const RenderRule SpriteComponent::Render() 
{
	auto pGo = GetGameObject().lock();
	auto pTransform = pGo->GetTransform().lock();

	auto spriteData = renderRule.GetData<SpriteRenderData>();
	spriteData->sprite.setPosition(pTransform->Position.x, pTransform->Position.y);

	return renderRule;
}

