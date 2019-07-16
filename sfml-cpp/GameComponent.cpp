#include "GameComponent.h"

void GameComponent::Init(std::weak_ptr<GameObject> owner)
{
	this->gameObject = owner;
}
