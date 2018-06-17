#include"Collision.h"

#include<math.h>

namespace gfunc
{
	bool Collision::ABRectToRect(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2)
	{
		if (x1 + w1 / 2 >= x2 - w2 / 2 && x1 - w1 / 2 <= x2 + w2 / 2
			&& y1 + h1 / 2 >= y2 - h2 / 2 && y1 - h1 / 2 <= y2 + h2 / 2)
		{
			return true;
		}
		return false;
	}

	bool Collision::ABRectToCircle(float x1, float y1, int w1, int h1, float x2, float y2, int d)
	{
		float left_x = x1 - w1 / 2;
		float right_x = x1 + w1 / 2;
		float up_y = y1 - h1 / 2;
		float down_y = y1 + h1 / 2;

		if ((left_x <= x2 && right_x >= x2) || (up_y <= y2 && down_y >= y2))
		{
			if ((x2 - d / 2 <= right_x) && (x2 + d / 2 >= left_x) && (y2 - d / 2 <= down_y) && (y2 + d / 2 >= up_y))
				return true;
		}
		else
		{
			float len = fabsf(left_x - x2)*fabsf(left_x - x2) + fabsf(up_y - y2)*fabsf(up_y - y2);//좌상단과 원 중심점
			if (len <= (d / 2)*(d / 2)) return true;
			len = fabsf(left_x - x2)*fabsf(left_x - x2) + fabsf(down_y - y2)*fabsf(down_y - y2);//좌하단과 원 중심점
			if (len <= (d / 2)*(d / 2)) return true;
			len = fabsf(right_x - x2)*fabsf(right_x - x2) + fabsf(up_y - y2)*fabsf(up_y - y2);//우상단과 원 중심점
			if (len <= (d / 2)*(d / 2)) return true;
			len = fabsf(right_x - x2)*fabsf(right_x - x2) + fabsf(down_y - y2)*fabsf(down_y - y2);//우하단과 원 중심점
			if (len <= (d / 2)*(d / 2)) return true;
		}

		return false;
	}

	bool Collision::OBRectToRect(Ver2 ver1, Size size1, Vec2 dir1, Ver2 ver2, Size size2, Vec2 dir2)
	{
		auto stdVecH1 = dir1 * size1.width / 2.0;
		auto stdVecV1 = Vector::getPerpVector(dir1) * size1.height / 2.0;
		auto stdVecH2 = dir2 * size2.width / 2.0;
		auto stdVecV2 = Vector::getPerpVector(dir2) * size2.height / 2.0;

		auto VecAtoB = ver2 - ver1;
		float rA, rB, D;

		rA = size1.width / 2.0;
		rB = Vector::Comp(stdVecH1, stdVecH2) + Vector::Comp(stdVecH1, stdVecV2);
		D = Vector::Comp(stdVecH1, VecAtoB);
		if (D > rA + rB) return false;

		rA = size1.height / 2.0;
		rB = Vector::Comp(stdVecV1, stdVecH2) + Vector::Comp(stdVecV1, stdVecV2);
		D = Vector::Comp(stdVecV1, VecAtoB);
		if (D > rA + rB) return false;

		rA = size2.width / 2.0;
		rB = Vector::Comp(stdVecH2, stdVecH1) + Vector::Comp(stdVecH2, stdVecV1);
		D = Vector::Comp(stdVecH2, VecAtoB);
		if (D > rA + rB) return false;

		rA = size2.height / 2.0;
		rB = Vector::Comp(stdVecV2, stdVecH1) + Vector::Comp(stdVecV2, stdVecV1);
		D = Vector::Comp(stdVecV2, VecAtoB);
		if (D > rA + rB) return false;

		return true;
	}

	bool Collision::OBRectToCircle(Ver2 ver1, Size size1, Vec2 dir1, Ver2 ver2, int d2)
	{
		float rectAngle = Vector::getAngle(dir1);
		Ver2 oldCircle = Ver2(ver2.x - ver1.x, ver2.y - ver1.y);
		float circleX = oldCircle.x * Math::Cos(rectAngle) - oldCircle.y * Math::Sin(rectAngle);
		float circleY = oldCircle.x * Math::Sin(rectAngle) + oldCircle.y * Math::Cos(rectAngle);
		
		return ABRectToCircle(0, 0, size1.width, size1.height, circleX, circleY, d2);
	}

	bool Collision::CircleToCircle(float x1, float y1, int d1, float x2, float y2, int d2)
	{
		float len = fabsf(x1 - x2)*fabsf(x1 - x2) + fabsf(y1 - y2)*fabsf(y1 - y2);

		if ((d1 / 2 + d2 / 2)*(d1 / 2 + d2 / 2) >= len) {
			return true;
		}
		return false;
	}

	bool Collision::PointToRect(float x1, float y1, float x2, float y2, int w, int h)
	{
		if (x1 >= x2 - w / 2 && x1 <= x2 + w / 2 && y1 >= y2 - h / 2 && y1 <= y2 + h / 2)
			return true;
		return false;
	}

	bool Collision::PointToCircle(float x1, float y1, float x2, float y2, int d)
	{
		float len = fabsf(x1 - x2)*fabsf(x1 - x2) + fabsf(y1 - y2)*fabsf(y1 - y2);

		if ((d / 2)*(d / 2) >= len)
			return true;
		return false;
	}
}