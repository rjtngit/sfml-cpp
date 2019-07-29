#include "Vector2.h"
#include "Level.h"
#include "GameInstance.h"
#include "GameConfig.h"

const Vector2 Vector2::Zero;

Vector2 Vector2::WorldToScreenPoint(Vector2 worldPoint, Vector2 cameraTarget, Vector2 nativeResolution)
{
	return Vector2(
		worldPoint.x - cameraTarget.x + nativeResolution.x / 2.0,
		worldPoint.y - cameraTarget.y + nativeResolution.y / 2.0
	);
}
