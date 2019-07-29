#include "AnimatedSpriteComponent.h"

void AnimatedSpriteComponent::Start()
{
	SpriteComponent::Start();

	cropTexture = true;

	if (cols > 0)
	{
		cropWidth = texWidth / cols;
	}

	if (rows > 0)
	{
		cropHeight = texHeight / rows;
	}

	frameTimeRemaining = frameTime;

	EnableTick(true);
}

void AnimatedSpriteComponent::Tick(float deltaTime)
{
	SpriteComponent::Tick(deltaTime);

	frameTimeRemaining -= deltaTime;

	if (frameTimeRemaining <= 0)
	{
		frameTimeRemaining = frameTime;
		currentCol++;
		if (currentCol >= cols)
		{
			currentCol = 0;
			currentRow++;

			if (currentRow >= rows)
			{
				currentRow = 0;
			}
		}

		cropLeft = cropWidth * currentCol;
		cropTop = cropHeight * currentRow;

	}
}

void AnimatedSpriteComponent::ResetToBeginning()
{
	currentCol = 0;
	currentRow = 0;
	frameTimeRemaining = frameTime;
}
