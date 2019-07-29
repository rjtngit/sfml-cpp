#pragma once
#include "GameComponent.h"
class BlockingComponent : public GameComponent
{
	LOADABLE_CLASS(BlockingComponent)

	//VARIABLES
public:
	LOADABLE_BOOL(blockPlayer)
	bool blockPlayer = true;

	LOADABLE_BOOL(blockBullet)
	bool blockBullet = true;
};