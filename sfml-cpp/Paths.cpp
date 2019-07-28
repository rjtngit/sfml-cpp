#include "Paths.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string Paths::GetInContentPath(std::string subPath)
{
	return "Content/" + subPath;

}

std::string Paths::GetLevelPath(std::string filename)
{
	return "Content/Levels/" + filename;
}

std::string Paths::GetObjectPath(std::string filename)
{
	return "Content/Objects/" + filename;
}

std::string Paths::GetFontPath(std::string filename)
{
	return "Content/Fonts/" + filename;
}

