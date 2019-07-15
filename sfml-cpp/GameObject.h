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

	bool IsInitialized() const { return initialized; }

	GameComponent* AddComponent(std::string className);

	template<typename T>
	T* AddComponent();

	template<typename T>
	T* GetComponent();

	void DeleteComponents();
	void StartComponents();
	void Update(float deltaTime);

	// VARIABLES
public:
	TransformComponent* transform = nullptr;

private:
	bool initialized = false;
	std::string name;
	std::vector<std::unique_ptr<GameComponent>> components;
	std::vector<std::unique_ptr<GameComponent>> newComponents;
	std::vector<std::unique_ptr<GameComponent>> deletedComponents;


	std::vector<std::unique_ptr<GameObject>> children;
};


// TEMPLATES
template<typename T>
T* GameObject::AddComponent()
{
	newComponents.push_back(std::make_unique<T>());
	return dynamic_cast<T*>(newComponents[newComponents.size() - 1].get());
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

	for (auto& comp : newComponents) 
	{
		T* obj = dynamic_cast<T*>(comp.get());
		if (obj)
		{
			return obj;
		}
	}

	return nullptr;
}

