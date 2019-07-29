#pragma once
#include "GameComponent.h"

class EnemyComponent : public GameComponent
{
public:
	virtual void Hit(int damage = 1);


protected:
	int damageTaken = 0;
	int maxHp = 10;
};