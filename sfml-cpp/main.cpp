#include "GameInstance.h"
#include "GameConfig.h"

int main()
{
	GameConfig config("Content/Game.ini");
	GameInstance gameInstance(config);

	while (gameInstance.IsRunning())
	{
		gameInstance.Update();
		gameInstance.Render();
	}

	return 0;
}