#pragma once

struct Rect
{
public:
	Rect(int left, int top, int width, int height)
	{
		this->left = left;
		this->top = top;
		this->width = width;
		this->height = height;
	}

	int left = 0;
	int top = 0;
	int width = 0;
	int height = 0;
};