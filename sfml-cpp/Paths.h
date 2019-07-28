#pragma once
#include <string>

namespace Paths
{
	std::string GetInContentPath(std::string subPath);

	std::string GetLevelPath(std::string filename);
	std::string GetObjectPath(std::string filename);
	std::string GetFontPath(std::string filename);


}