#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "GameComponent.h"

class TransformComponent;

class GameObject
{
public: 
	GameObject();
	void Init(std::string name, int x, int y);
	void Init(int x, int y);
	void InitFromFile(std::string path);
	void InitFromFile(std::string path, int overrideX, int overrideY);

	GameComponent* AddComponent(std::string className);

	template<typename T, typename... ARGS>
	T* AddComponent(ARGS... args);

	template<typename T>
	T* GetComponent();

	// VARIABLES
public:
	TransformComponent* transform = nullptr;

private:
	bool initialized = false;
	std::string name;
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

template<typename T>
T* GameObject::GetComponent()
{
	for (auto& comp : components) 
	{
		T* obj = dynamic_cast<T*>(comp.get());
		if (obj)
		{
			return obj;
		}

	}

	return nullptr;
}

