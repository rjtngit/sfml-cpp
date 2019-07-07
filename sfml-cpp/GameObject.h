#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "GameComponent.h"

class GameObject
{
public: 
	GameObject(int x, int y);

	void InitFromFile(std::string path);

	template<typename T, typename... ARGS>
	T* AddComponent(ARGS... args);

	// VARIABLES
private:
	std::vector<std::unique_ptr<GameComponent>> components;
	std::vector<std::unique_ptr<GameObject>> children;
};


// TEMPLATES
template<typename T, typename... ARGS>
T* GameObject::AddComponent(ARGS... args)
{
	components.push_back(std::make_unique<T>(args...));
	return dynamic_cast<T*>(components[components.size() - 1].get());
}
