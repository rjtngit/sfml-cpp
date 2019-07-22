#include "BoxColliderComponent.h"
#include <memory>
#include "GameObject.h"
#include "TransformComponent.h"
#include "Level.h"



void BoxColliderComponent::Start()
{

}

void BoxColliderComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();

	rect.left = transform->Position.x + offsetX;
	rect.top = transform->Position.y + offsetY;
	rect.width = width;
	rect.height = height;
}

RenderRule BoxColliderComponent::GetRenderRule()
{
	if (debugDraw)
	{
		RenderRule renderRule;
		renderRule.render = true;
		renderRule.gameComponent = this;
		renderRule.order = INT_MAX;

		return renderRule;
	}

	return RenderRule::NoRender;
}

void BoxColliderComponent::Render(GameRenderer& target)
{
	target.DrawRect(Vector2(rect.left, rect.top), Vector2(rect.width, rect.height));
}

bool BoxColliderComponent::IsCollidingAny()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	// hack to make sure the rect is up to date
	// TODO update rect whenever transform position is set?
	{
		rect.left = transform->Position.x + offsetX;
		rect.top = transform->Position.y + offsetY;
		rect.width = width;
		rect.height = height;
	}

	// also hacky
	// TODO optimize 
	for (auto pObj : level->GetObjects())
	{
		auto obj = pObj.lock();
		auto pCol = obj->GetComponent<BoxColliderComponent>();
		if (!pCol.expired())
		{
			auto col = pCol.lock();
			if (col == shared_from_this())
			{
				continue;
			}

			if (col->rect.intersects(rect))
			{
				return true;
			}
		}
	}

	return false;
}

