#pragma once
#include <map>
#include <functional>
#include <string>

class GameComponent
{

public:
	virtual ~GameComponent() = default;
	virtual void Update(float deltaTime) = 0;

};

class BaseComponentLoader
{
public:
	static GameComponent* CreateNew(std::string className);
	static std::map<std::string, std::function<GameComponent*()>> LoaderFuncs;
};
