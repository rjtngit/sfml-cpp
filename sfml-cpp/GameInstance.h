#pragma once

#include "Level.h"
#include "GameConfig.h"
#include "GameWindow.h"

class GameInstance
{
public:
	GameInstance(GameConfig config);
	void Update();
	void Render();
	bool IsRunning() const;
	const GameConfig GetGameConfig() const;

private:
	std::shared_ptr<Level> activeLevel;
	GameWindow window;
	sf::Clock deltaClock;
	GameConfig config;
};