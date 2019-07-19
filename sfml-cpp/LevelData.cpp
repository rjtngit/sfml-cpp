#include "LevelData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Paths.h"
#include "GameObject.h"

LevelData::LevelData(std::string path)
{
	std::ifstream file(path);
	if (file.is_open())
	{
		// load data from file
		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string curLine;

		DataType dataType = DataType::UNDEFINED;
		int mapRow = 0;

		while (std::getline(buffer, curLine))
		{
			if (curLine.empty())
			{
				continue;
			}
			// Set current data type
			else if (curLine == "PROPERTIES:")
			{
				dataType = DataType::PROPERTY;
				continue;
			}
			else if (curLine == "OBJECTS:")
			{
				dataType = DataType::OBJECT;
				continue;
			}
			else if (curLine == "LAYOUT:")
			{
				dataType = DataType::LAYOUT;
				continue;
			}
			// Read data
			else if (dataType == DataType::PROPERTY)
			{
				ReadProperty(curLine);
				continue;
			}
			else if (dataType == DataType::OBJECT)
			{
				ReadObject(curLine);
				continue;
			}
			else if (dataType == DataType::LAYOUT)
			{
				ReadMapRow(curLine, mapRow);
				mapRow++;
				continue;
			}

			// How did we get this far?
			std::cout << "LevelData::LevelData - Failed to parse line: '" << curLine << "'" << std::endl;
		}
	}
	else
	{
		std::cout << "LevelData::LevelData - Unable to open file " << path << std::endl;
	}
}

void LevelData::ReadProperty(std::string line)
{
	size_t splitIndex = line.find('=');
	if (splitIndex == std::string::npos)
	{
		return;
	}

	std::string key = line.substr(0, splitIndex);
	std::string value = line.substr(splitIndex + 1);

	if (key.empty())
	{
		return;
	}
	else if (key == "LevelName")
	{
		levelName = value;
	}
	else if (key == "TileWidth")
	{
		tileSize.x = std::stof(value);
	}
	else if (key == "TileHeight")
	{
		tileSize.y = std::stof(value);
	}
}

void LevelData::ReadObject(std::string line)
{
	size_t splitIndex = line.find('=');
	if (splitIndex == std::string::npos)
	{
		return;
	}

	std::string key = line.substr(0, splitIndex);
	std::string value = line.substr(splitIndex + 1);

	if (key.empty())
	{
		return;
	}
	
	objectFiles.insert(std::make_pair(key[0], value));
}

void LevelData::ReadMapRow(std::string line, int rowIndex)
{
	int x = 0;
	int y = rowIndex;

	for (size_t i = 0; i < line.size(); ++i, ++x)
	{
		char objectId = line[i];
		auto it = objectFiles.find(objectId);
		if (it == objectFiles.end())
		{
			std::cout << "LevelData::ReadMapRow: Object with ID '" << objectId << "' not found." << std::endl;
			continue;
		}

		ObjectData objData;
		objData.fileName = it->second;
		objData.worldPosition = Vector2(x * tileSize.x, y * tileSize.y);

		layoutData.push_back(objData);
	}
}
