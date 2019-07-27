#pragma once
#include "EnemyComponent.h"

class FloatingEnemyComponent : public EnemyComponent
{
	LOADABLE_CLASS(FloatingEnemyComponent)

public:
	void Tick(float deltaTime) override;

};