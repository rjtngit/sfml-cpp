#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

struct RenderData
{
public:
	virtual ~RenderData() = default;
};


struct SpriteRenderData : public RenderData
{
public:
	sf::Texture texture;
	sf::Sprite sprite;
};


// ---------------------//


struct RenderRule
{
public:
	static const RenderRule NoRender;

	template <typename T>
	std::shared_ptr<T> InitData()
	{
		data = std::make_shared<T>();
		return GetData<T>();
	}

	template <typename T> 
	std::shared_ptr<T> GetData() const
	{
		return std::dynamic_pointer_cast<T>(data);
	}

	operator bool() const { return data != nullptr; }

private:
	std::shared_ptr<RenderData> data;
};



