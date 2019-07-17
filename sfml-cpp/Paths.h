#pragma once
#include <string>

namespace Paths
{
	std::string GetLevelPath(std::string filename);
	std::string GetObjectPath(std::string filename);
	std::string FindObjectPath(const std::string objData, const char objIdentifier);
	std::string GetInContentPath(std::string subPath);

}