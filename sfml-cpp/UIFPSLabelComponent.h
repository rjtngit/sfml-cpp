#pragma once
#include "GameComponent.h"
#include "UILabelComponent.h"

class UIFPSLabelComponent : public GameComponent
{
	LOADABLE_CLASS(UIFPSLabelComponent)

public:
	void Start() override;
	void Tick(float deltaTime) override;

private:
	std::weak_ptr<UILabelComponent> pLabel;
};