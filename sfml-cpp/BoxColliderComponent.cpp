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

bool BoxColliderComponent::IsCollidingWithAnything()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	// Start test at last rect position (i.e. set at start of frame)
	sf::IntRect testRect = rect;
	testRect.left = transform->Position.x + offsetX;
	testRect.top = transform->Position.y + offsetY;

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

			if (col->rect.intersects(testRect))
			{
				return true;
			}
		}
	}

	return false;
	
}

