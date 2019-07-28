#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "GameComponent.h"
#include <set>
#include <unordered_set>

class Level;
class TransformComponent;

class GameObject : public std::enable_shared_from_this<GameObject>
{
public: 
	void Init(std::weak_ptr<Level> level, std::string name, float x, float y);
	void Init(std::weak_ptr<Level> level, float x, float y);
	void InitFromFile(std::weak_ptr<Level> level, std::string path);
	void InitFromFile(std::weak_ptr<Level> level, std::string path, float overrideX, float overrideY);

	std::weak_ptr<GameComponent> AddComponent(std::string className);

	template<typename T>
	std::weak_ptr<T> AddComponent();

	template<typename T>
	std::weak_ptr<T> GetComponent();

	std::weak_ptr<Level> GetLevel() { return level; }
	std::weak_ptr<TransformComponent> GetTransform() const { return transform;  }

	void DestroyComponent(std::weak_ptr<GameComponent> component);
	void StartComponents();
	void TickComponents(float deltaTime);

	void RegisterForTick(std::weak_ptr<GameComponent> component);
	void UnregisterForTick(std::weak_ptr<GameComponent> component);
	void RegisterForRender(std::weak_ptr<GameComponent> component);
	void UnregisterForRender(std::weak_ptr<GameComponent> component);
	void RegisterForStart(std::weak_ptr<GameComponent> component);
	void UnregisterForStart(std::weak_ptr<GameComponent> component);

	void AppendRenderRules(std::vector<RenderRule>& rules) const;

	// VARIABLES
private:
	std::string name;

	std::weak_ptr<Level> level;
	std::weak_ptr<TransformComponent> transform;

	std::unordered_set<std::shared_ptr<GameComponent>> components;
	std::unordered_set<std::shared_ptr<GameComponent>> newComponents;
	std::unordered_set<std::shared_ptr<GameComponent>> tickComponents;
	std::unordered_set<std::shared_ptr<GameComponent>> renderComponents;
};


// TEMPLATES
template<typename T>
std::weak_ptr<T> GameObject::AddComponent()
{
	std::shared_ptr<T> comp = std::make_shared<T>();
	comp->Init(shared_from_this());
	components.insert(comp);

	return comp;
}

template<typename T>
std::weak_ptr<T> GameObject::GetComponent()
{
	std::shared_ptr<T> result = nullptr;

	for (auto& comp : components)
	{
		result = std::dynamic_pointer_cast<T>(comp);
		if (result)
		{
			return result;
		}
	}

	return result;
}

