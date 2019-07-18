#include "GameWindow.h"
#include "RenderRule.h"

GameWindow::GameWindow(int width, int height, std::string title)
	:
	renderWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title)),
	renderer(renderWindow)
{
}

void GameWindow::Update()
{
	sf::Event event;
	while (renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			renderWindow->close();
	}
}

void GameWindow::Render(const Level* level)
{
	renderWindow->clear();

	std::vector<RenderRule> rules;
	level->GetRenderRules(rules);

	std::sort(rules.begin(), rules.end(), [](const RenderRule &a, const RenderRule &b)
	{
		return a.order < b.order;
	});

	for (const auto& r : rules)
	{
		if (r.render && r.gameComponent)
		{
			r.gameComponent->Render(renderer);
		}
	}

	renderWindow->display();
}

bool GameWindow::IsOpen() const
{
	return renderWindow->isOpen();
}
