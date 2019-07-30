#include "RestartGameTimerComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "GameInstance.h"

void RestartGameTimerComponent::Start()
{
	EnableTick(true);
}

void RestartGameTimerComponent::Tick(float deltaTime)
{
	timeLeft -= deltaTime;
	if(timeLeft <= 0)
	{
		auto go = GetGameObject().lock();
		auto level = go->GetLevel().lock();

		level->GetGameInstance()->RestartGame();

	}
}
