#include "GameInstance.h"
#include "Level.h"
#include "Paths.h"
#include "RenderRule.h"
#include "Vector2.h"

GameInstance::GameInstance(GameConfig config)
	: 
	window(config.GetWindowWidth(), config.GetWindowHeight(), config.GetGameTitle()),
	activeLevel(std::make_unique<Level>(Paths::GetLevelPath(config.GetStartLevelFileName())))
{
	deltaClock.restart();
}

void GameInstance::Update()
{
	window.Update();

	sf::Time dt = deltaClock.restart();
	activeLevel->Update(dt.asSeconds());
}

void GameInstance::Render()
{
	window.Render(activeLevel.get());
}

bool GameInstance::IsRunning() const
{
	return window.IsOpen();
}
