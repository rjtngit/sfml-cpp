#include "SwordKillBoxComponent.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "Level.h"

void SwordKillBoxComponent::Start()
{
	EnableTick(true);
}

void SwordKillBoxComponent::Tick(float deltaTime)
{
	elapsed += deltaTime;

	if (elapsed >= delay)
	{
		auto go = GetGameObject().lock();
		auto transform = go->GetTransform().lock();
		auto collider = go->GetComponent<BoxColliderComponent>().lock();
		auto level = go->GetLevel().lock();

		auto pHitPlayer = collider->GetOverlappingComponent<PlayerComponent>();
		if (!pHitPlayer.expired())
		{
			pHitPlayer.lock()->HitBySword();
		}

		level->DestroyObject(go);
	}


}
