#include "Paths.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string Paths::GetLevelPath(std::string filename)
{
	return "Content/Levels/" + filename;
}

std::string Paths::GetObjectPath(std::string filename)
{
	return "Content/Objects/" + filename;
}

std::string Paths::FindObjectPath(const std::string objData, const char objIdentifier)
{
	std::istringstream dataStream(objData);
	std::string curLine;
	while (std::getline(dataStream, curLine))
	{
		size_t splitIndex = curLine.find('=');
		if (splitIndex == std::string::npos)
		{
			continue;
		}

		std::string id = curLine.substr(0, splitIndex);
		if (id.size() == 1 && id[0] == objIdentifier)
		{
			// found matching char. return file name (string on right side of '=')
			return Paths::GetObjectPath(curLine.substr(splitIndex + 1));
		}
	}

	std::cout << "Paths::FindObjectPath - Key not found: " << objIdentifier << std::endl;
	return "";
}