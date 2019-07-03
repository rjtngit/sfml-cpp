#include "GameInstance.h"

int main()
{
	GameInstance gameInstance;

	while (gameInstance.IsRunning())
	{
		gameInstance.Update();
		gameInstance.Render();
	}

	return 0;
}