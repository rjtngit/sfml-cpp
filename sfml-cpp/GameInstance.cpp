#include "GameInstance.h"
#include "Level.h"
#include "Paths.h"

GameInstance::GameInstance() 
	: 
	window(sf::VideoMode(640, 360), ""),
	activeLevel(std::make_unique<Level>(Paths::GetLevelPath("Start.lvl")))
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
