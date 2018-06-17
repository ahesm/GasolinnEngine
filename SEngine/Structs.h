#pragma once

#include<SDL.h>

namespace gasolinn
{
	struct Size
	{
	public:
		Size(int w = 0, int h = 0) { width = w; height = h; }
		int width, height;
	};

	struct Color
	{
	public:
		Color(int r = 0, int g = 0, int b = 0) { this->r = r; this->g = g; this->b = b; }
		int r, g, b;
	};

	struct Rect
	{
	public:
		Rect(float x = 0, float y = 0, int w = 0, int h = 0) { this->x = x; this->y = y; this->w = w; this->h = h; }
		float x, y;
		int w, h;
	};

}