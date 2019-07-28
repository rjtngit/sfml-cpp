#include "UIFPSLabelComponent.h"
#include <memory>
#include "GameComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"


void UIFPSLabelComponent::Start()
{
	auto go = GetGameObject().lock();
	auto transform = go->GetTransform().lock();

	transform->Position = Vector2::Zero;

	pLabel = go->AddComponent<UILabelComponent>();
}

void UIFPSLabelComponent::Tick(float deltaTime)
{
	float fps = 1.0f / deltaTime;

	auto label = pLabel.lock();
	label->text = "FPS: " + std::to_string(fps);
}
