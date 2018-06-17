#pragma once

#include"Vector.h"

#include"Structs.h"

using namespace gasolinn;

namespace gfunc
{
	class Collision
	{
	public:
		static bool ABRectToRect(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);
		static bool ABRectToCircle(float x1, float y1, int w1, int h1, float x2, float y2, int d);
		static bool CircleToCircle(float x1, float y1, int d1, float x2, float y2, int d2);
		static bool PointToRect(float x1, float y1, float x2, float y2, int w, int h);
		static bool PointToCircle(float x1, float y1, float x2, float y2, int d);
		static bool OBRectToRect(Ver2 ver1, Size size1, Vec2 dir1, Ver2 ver2, Size size2, Vec2 dir2);
		static bool OBRectToCircle(Ver2 ver1, Size size1, Vec2 dir1, Ver2 ver2, int d2);
	};
}