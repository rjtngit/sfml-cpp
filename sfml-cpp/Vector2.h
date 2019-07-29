#pragma once

class Level;

struct Vector2
{
	// VARIABLES
public:
	static const Vector2 Zero;
	static Vector2 WorldToScreenPoint(Vector2 worldPoint, Vector2 cameraTarget, Vector2 nativeResolution);

	// METHODS
public:
	Vector2() {}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator+ (const Vector2 & other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator- (const Vector2 & other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator* (const float & v) const
	{
		return Vector2(x * v, y * v);
	}


// VARIABLES
public:
	float x = 0.0f;
	float y = 0.0f;
};