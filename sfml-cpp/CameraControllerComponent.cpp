#include "CameraControllerComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Level.h"
#include "PlayerComponent.h"

void CameraControllerComponent::Start()
{
	EnableTick(true);
}

void CameraControllerComponent::Tick(float deltaTime)
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();
	auto level = go->GetLevel().lock();

	auto objs = level->GetObjects();
	int numPlayers = 0;
	int xTotal = 0;
	for (auto pObj : objs)
	{
		auto o = pObj.lock();
		auto pPlayer = o->GetComponent<PlayerComponent>();
		if (!pPlayer.expired())
		{
			auto player = pPlayer.lock();
			auto playerGo = player->GetGameObject().lock();
			auto PlayerT = playerGo->GetTransform().lock();

			xTotal += PlayerT->Position.x;
			numPlayers++;
		}
	}

	// Position camera between players
	Vector2 cameraPos = Vector2(xTotal / numPlayers, 420);
	level->SetCameraTarget(cameraPos);
}
