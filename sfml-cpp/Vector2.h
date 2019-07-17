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

// VARIABLES
public:
	float x = 0.0f;
	float y = 0.0f;
};