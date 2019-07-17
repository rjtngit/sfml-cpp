#include "GameInstance.h"
#include "Level.h"
#include "Paths.h"
#include "RenderRule.h"

GameInstance::GameInstance(GameConfig config)
	: 
	window(sf::VideoMode(config.GetWindowWidth(), config.GetWindowHeight()), config.GetGameTitle()),
	activeLevel(std::make_unique<Level>(Paths::GetLevelPath(config.GetStartLevelFileName())))
{
	deltaClock.restart();
}

void GameInstance::Update()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}

	sf::Time dt = deltaClock.restart();
	activeLevel->Update(dt.asSeconds());
}

void GameInstance::Render()
{
	window.clear();

	std::vector<RenderRule> rules;
	activeLevel->GetRenderRules(rules);

	for (const auto& r : rules)
	{
		if (r)
		{
			auto spriteData = r.GetData<SpriteRenderData>();
			if (spriteData)
			{
				window.draw(spriteData->sprite);
			}
		}
	}

	window.display();
}

bool GameInstance::IsRunning() const
{
	return window.isOpen();
}
