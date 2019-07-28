#include "UILabelComponent.h"
#include "Vector2.h"
#include "GameObject.h"
#include "GameComponent.h"
#include "TransformComponent.h"
#include "Paths.h"


void UILabelComponent::Start()
{
	EnableRender(true);
}

RenderRule UILabelComponent::GetRenderRule()
{
	RenderRule renderRule;
	renderRule.render = true;
	renderRule.gameComponent = this;
	renderRule.order = INT_MAX;

	return renderRule;
}

void UILabelComponent::Render(GameRenderer& target)
{
	target.DrawText(text, Paths::GetFontPath(font), GetGameObject().lock()->GetTransform().lock()->Position);
}
