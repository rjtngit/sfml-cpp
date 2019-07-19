#pragma once
#include <string>
#include <vector>
#include <map>
#include "Vector2.h"

class LevelData
{
public:
	enum class DataType
	{
		UNDEFINED,
		PROPERTY,
		OBJECT,
		LAYOUT
	};

	class ObjectData
	{
	public:
		Vector2 worldPosition;
		std::string fileName;
	};

	// METHODS
public:
	LevelData(std::string path);

	std::string GetLevelName() const { return levelName; }
	Vector2 GetTileSize() const { return tileSize; }
	const std::vector<ObjectData>& GetLayout() const { return layoutData; }

private:
	void ReadProperty(std::string line);
	void ReadObject(std::string line);
	void ReadMapRow(std::string line, int rowIndex);

	// VARIABLES
private:
	std::string levelName;
	Vector2 tileSize;

	std::map<char, std::string> objectFiles;
	std::vector<ObjectData> layoutData;
};