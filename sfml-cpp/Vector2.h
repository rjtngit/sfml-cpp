#pragma once

struct Vector2
{
public:
	Vector2() {}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator+ (const Vector2 & first) const
	{
		return Vector2(x + first.x, y + first.y);
	}

	Vector2 operator- (const Vector2 & first) const
	{
		return Vector2(x - first.x, y - first.y);
	}

// VARIABLES
public:
	float x = 0.0f;
	float y = 0.0f;
};