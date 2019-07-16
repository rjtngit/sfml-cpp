#pragma once
#include <string>

class GameConfig
{

public:
	GameConfig(std::string file);

	std::string GetGameTitle() const { return gameTitle; };
	std::string GetStartLevelFileName() const { return startLevelFileName; };
	int GetWindowWidth() const { return windowWidth; };
	int GetWindowHeight() const { return windowHeight; };

private:
	std::string gameTitle = "Game";
	std::string startLevelFileName = "Start.lvl";
	int windowWidth = 1024;
	int windowHeight = 768;

};