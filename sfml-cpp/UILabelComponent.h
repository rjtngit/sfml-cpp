#pragma once
#include "GameComponent.h"

class UILabelComponent : public GameComponent
{
	LOADABLE_CLASS(UILabelComponent)

public:
	void Start() override;
	RenderRule GetRenderRule() override;
	void Render(GameRenderer& target) override;



	// VARIABLES
public:
	LOADABLE_STRING(text)
	std::string text;
	std::string font = "arial.ttf";
};