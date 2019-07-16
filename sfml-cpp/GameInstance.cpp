#include "GameInstance.h"
#include "Level.h"
#include "Paths.h"

GameInstance::GameInstance(GameConfig config)
	: 
	window(sf::VideoMode(config.GetWindowWidth(), config.GetWindowHeight()), config.GetGameTitle()),
	activeLevel(std::make_unique<Level>(Paths::GetLevelPath(config.GetStartLevelFileName())))
{
	deltaClock.restart();
}

void GameInstance::Update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	sf::Time dt = deltaClock.restart();
	activeLevel->Update(dt.asSeconds());
}

void GameInstance::Render()
{
	window.clear();
//	window.draw();
	window.display();
}

bool GameInstance::IsRunning() const
{
	return window.isOpen();
}
