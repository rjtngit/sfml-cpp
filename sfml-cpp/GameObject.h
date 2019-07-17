#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "GameComponent.h"

class TransformComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public: 
	void Init(std::string name, float x, float y);
	void Init(float x, float y);
	void InitFromFile(std::string path);
	void InitFromFile(std::string path, float overrideX, float overrideY);

	bool IsInitialized() const { return initialized; }

	std::weak_ptr<GameComponent> AddComponent(std::string className);

	template<typename T>
	std::weak_ptr<T> AddComponent();

	template<typename T>
	std::weak_ptr<T> GetComponent();

	std::weak_ptr<TransformComponent> GetTransform() { return transform;  }

	void DestroyComponent(std::weak_ptr<GameComponent> component);

	void Update_DestroyComponents();
	void Update_StartComponents();
	void Update_TickComponents(float deltaTime);

	void AppendRenderRules(std::vector<RenderRule>& rules) const;

	// VARIABLES
private:
	bool initialized = false;
	std::string name;

	std::weak_ptr<TransformComponent> transform;

	std::vector<std::shared_ptr<GameComponent>> activeComponents;
	std::vector<std::shared_ptr<GameComponent>> newComponents;
	std::vector<std::shared_ptr<GameComponent>> destroyedComponents;
};


// TEMPLATES
template<typename T>
std::weak_ptr<T> GameObject::AddComponent()
{
	std::shared_ptr<T> comp = std::make_shared<T>();
	comp->Init(shared_from_this());
	newComponents.push_back(comp);
	return comp;
}

template<typename T>
std::weak_ptr<T> GameObject::GetComponent()
{
	for (auto& comp : activeComponents) 
	{
		std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(comp);
		if (obj)
		{
			return obj;
		}
	}

	for (auto& comp : newComponents)
	{
		std::shared_ptr<T> obj = std::dynamic_pointer_cast<T>(comp);
		if (obj)
		{
			return obj;
		}
	}

	return nullptr;
}

