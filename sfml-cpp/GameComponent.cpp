#include "GameComponent.h"

void GameComponent::Init(std::shared_ptr<GameObject> owner)
{
	this->gameObject = owner;
}
