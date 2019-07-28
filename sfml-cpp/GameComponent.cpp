#include "GameComponent.h"
#include "GameObject.h"

void GameComponent::Init(std::weak_ptr<GameObject> owner)
{
	this->gameObject = owner;
	this->gameObject.lock()->RegisterForStart(shared_from_this());
}

void GameComponent::EnableTick(bool enabled)
{
	if (canTick != enabled)
	{
		canTick = enabled;

		if (canTick)
		{
			GetGameObject().lock()->RegisterForTick(shared_from_this());
		}
		else
		{
			GetGameObject().lock()->UnregisterForTick(shared_from_this());
		}
	}
}

void GameComponent::EnableRender(bool enabled)
{
	if (canRender != enabled)
	{
		canRender = enabled;

		if (canRender)
		{
			GetGameObject().lock()->RegisterForRender(shared_from_this());
		}
		else
		{
			GetGameObject().lock()->UnregisterForRender(shared_from_this());
		}
	}
}
