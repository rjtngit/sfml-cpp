#include "GameInstance.h"
#include "Level.h"
#include "Paths.h"
#include "RenderRule.h"
#include "Vector2.h"

GameInstance::GameInstance(GameConfig config)
	: 
	config(config),
	window(config.GetWindowWidth(), config.GetWindowHeight(), config.GetGameTitle()),
	activeLevel(std::make_shared<Level>(this, Paths::GetLevelPath(config.GetStartLevelFileName())))
{
	activeLevel->LoadData();
	deltaClock.restart();
}

void GameInstance::Update()
{
	float dt = deltaClock.restart().asSeconds();

	float fps = 1.0f / dt;
	if (fps <= 5.0f)
	{
		// Hack for very low fps or game freeze (e.g. moving the window around). Stop update so physics doesn't break.
		dt = 0;
	}

	activeLevel->Update(dt);
	window.Update();
}

void GameInstance::Render()
{
	window.Render(activeLevel.get());
}

bool GameInstance::IsRunning() const
{
	return window.IsOpen();
}
