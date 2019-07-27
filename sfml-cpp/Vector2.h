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