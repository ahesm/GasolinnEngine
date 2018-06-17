#pragma once

namespace gfunc
{
	class Math
	{
	private:
		static double sinTable[3600];
		static double cosTable[3600];
		static double tanTable[3600];

	public:
		static void CreateTable();

		static double Sin(double value);
		static double Cos(double value);
		static double Tan(double value);

		static double FastInvSqrt(double value);
		static double FastSqrt(double value) { return FastInvSqrt(value) * value; };
		
		static float PointToDistance(float x1, float y1, float x2, float y2);
		static float PointToDirection(float x1, float y1, float x2, float y2);
	};

}