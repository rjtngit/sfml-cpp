#pragma once
#include "GameComponent.h"
#include "SFML/Graphics/Rect.hpp"
#include "GameObject.h"

class BoxColliderComponent : public GameComponent
{
	LOADABLE_CLASS(BoxColliderComponent)

private:
	void Start() override;
	RenderRule GetRenderRule() override;
	void Render(GameRenderer& target) override;
	bool Intersects(const BoxColliderComponent* other) const;

public:
	std::vector<std::weak_ptr<GameObject>> GetOverlappingObjects();
	bool IsOverlappingAnything();

	template<typename T>
	std::weak_ptr<T> GetOverlappingComponent();

	template<typename T>
	bool IsOverlappingComponent();

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

	bool debugDraw = false;
};

template<typename T>
std::weak_ptr<T>
BoxColliderComponent::GetOverlappingComponent()
{
	for (auto pObj : GetOverlappingObjects())
	{
		auto obj = pObj.lock();
		auto pCol = obj->GetComponent<T>();
		if (!pCol.expired())
		{
			return pCol;
		}
	}

	std::shared_ptr<T> result = nullptr;
	return result;
}

template<typename T>
bool BoxColliderComponent::IsOverlappingComponent()
{
	return !GetOverlappingComponent<T>().expired();
}
