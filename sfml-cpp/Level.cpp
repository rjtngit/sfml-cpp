#include "Level.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Paths.h"
#include "GameObject.h"


// --- METHODS --- //

Level::Level(std::string path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		// load data from file
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string data = buffer.str();

		// split map and object data
		size_t splitIndex = data.find('!');
		std::string mapData = data.substr(0, splitIndex);
		std::string objData = data.substr(splitIndex + 1);

		// iterate over tiles and create objects
		std::istringstream mapStream(mapData);
		std::string mapRow;
		int x = 0;
		int y = 0;
		while (std::getline(mapStream, mapRow))
		{
			for (size_t i = 0; i < mapRow.size(); ++i) 
			{
				// create object
				std::string objPath = Paths::FindObjectPath(objData, mapRow[i]);
				GameObject* obj = SpawnObject(x, y);
				obj->InitFromFile(objPath);

				++x;
			}

			x = 0;
			++y;
		}
	}
	else
	{
		std::cout << "Level::Level - Unable to open file " << path << std::endl;
	}
}

GameObject* Level::SpawnObject(int x, int y)
{
	objects.push_back(std::make_unique<GameObject>(x, y));
	return objects[objects.size() - 1].get();
}
