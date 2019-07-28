#include "BoxColliderComponent.h"
#include <memory>
#include "GameObject.h"
#include "TransformComponent.h"
#include "Level.h"
#include "SFML/Graphics/Rect.hpp"



void BoxColliderComponent::Start()
{
	EnableRender(debugDraw);
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
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();

	target.DrawRect(transform->Position, Vector2(width, height));
}

bool BoxColliderComponent::Intersects(const BoxColliderComponent* other) const
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();

	auto otherGo = other->GetGameObject().lock();
	auto otherTransform = otherGo->GetTransform().lock();

	sf::IntRect thisRect;
	thisRect.left = transform->Position.x + offsetX;
	thisRect.top = transform->Position.y + offsetY;
	thisRect.width = width;
	thisRect.height = height;

	sf::IntRect otherRect;
	otherRect.left = otherTransform->Position.x + other->offsetX;
	otherRect.top = otherTransform->Position.y + other->offsetY;
	otherRect.width = other->width;
	otherRect.height = other->height;

	return thisRect.intersects(otherRect);
}


std::vector<std::weak_ptr<GameObject>> BoxColliderComponent::GetOverlappingObjects()
{
	std::vector<std::weak_ptr<GameObject>> result;

	auto go = GetGameObject().lock();
	auto level = go->GetLevel().lock();

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

			if (col->Intersects(this))
			{
				result.push_back(pObj);
			}
		}
	}

	return result;
}

bool BoxColliderComponent::IsOverlappingAnything()
{
	return GetOverlappingObjects().size() > 0;
	
}

