#include "EnemyComponent.h"
#include "Level.h"
#include "GameObject.h"

void EnemyComponent::Hit(int damage /*= 1*/)
{
	auto go = GetGameObject().lock();
	auto level = go->GetLevel().lock();

	damageTaken += damage;

	if (damageTaken >= maxHp)
	{
		level->DestroyObject(go);
	}
}
