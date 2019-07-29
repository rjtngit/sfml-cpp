#pragma once
#include "GameComponent.h"

class CameraControllerComponent : public GameComponent
{
	LOADABLE_CLASS(CameraControllerComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;

};