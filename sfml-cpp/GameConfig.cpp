#include "GameConfig.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

GameConfig::GameConfig(std::string iniPath)
{
	std::ifstream file(iniPath);
	if (file.is_open())
	{
		// load data from file
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string curLine;

		while (std::getline(buffer, curLine))
		{
			size_t splitIndex = curLine.find('=');
			if (splitIndex == std::string::npos)
			{
				continue;
			}

			std::string key = curLine.substr(0, splitIndex);
			std::string value = curLine.substr(splitIndex + 1);

			if(key.empty())
			{
				continue;
			}
			else if(key == "GameTitle")
			{
				gameTitle = value;
			}
			else if(key == "StartLevel")
			{
				startLevelFileName = value;
			}
			else if(key == "WindowWidth")
			{
				windowWidth = std::stoi(value);
			}
			else if(key == "WindowHeight")
			{
				windowHeight = std::stoi(value);
			}
		}
	}
	else
	{
		std::cout << "GameConfig::GameConfig - Unable to open file " << iniPath << std::endl;
	}
}
