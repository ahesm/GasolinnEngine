#pragma once

#include"Math.h"
#include<math.h>

namespace gfunc
{
	struct Ver2;

	struct Vec2
	{
		Vec2(float x = 0, float y = 0) { this->x = x, this->y = y; }
		Vec2(Ver2 ver);
		float x, y;

		inline Vec2 operator +(Vec2 v) { return Vec2(this->x + v.x, this->y + v.y); }
		inline Vec2 operator -(Vec2 v) { return Vec2(this->x - v.x, this->y - v.y); }
		inline float operator *(Vec2 v) { return this->x*v.x + this->y*v.y; }
		inline Vec2 operator *(float f) { return Vec2(this->x*f, this->y*f); }
		inline Vec2 operator /(float f) { return Vec2(this->x / f, this->y / f); }
	};

	struct Ver2
	{
		Ver2(float x = 0, float y = 0) { this->x = x, this->y = y; }
		Ver2(Vec2 vec);
		float x, y;

		inline Ver2 operator +(Ver2 v) { return Ver2(this->x + v.x, this->y + v.y); };
		inline Ver2 operator -(Ver2 v) { return Ver2(this->x - v.x, this->y - v.y); };
		inline Ver2 operator +(Vec2 v) { return Ver2(this->x + v.x, this->y + v.y); };
		inline Ver2 operator -(Vec2 v) { return Ver2(this->x - v.x, this->y - v.y); };
		inline Ver2& operator +=(Vec2 v) { *this = Ver2(this->x + v.x, this->y + v.y); return *this; };
		inline Ver2& operator -=(Vec2 v) { *this = Ver2(this->x - v.x, this->y - v.y); return *this; };
	};



	class Vector
	{
	public:
		static inline float Size(Vec2 v){ return gfunc::Math::FastSqrt(v.x*v.x+v.y*v.y);}
		//Vector
		static inline Vec2 Proj(Vec2 vp, Vec2 vm) {float s = Size(vp); return vp * ( (vp*vm) / s*s ); }
		//Scalar
		static inline float Comp(Vec2 vp, Vec2 vm) { return fabsf( (vp * vm) / Size(vp) ); }

		static inline Vec2 getPerpVector(Vec2 v) { return Vec2(-v.y,v.x); }

		static inline Vec2 getNormVector(Vec2 v) { return v / Size(v); }

		static inline float getAngle(Vec2 v1, Vec2 v2) { return acos((v1*v2) / (Size(v1)*Size(v2))); }

		static inline float getAngle(Vec2 v) { return getAngle(Vec2(1, 0), v); }

		static inline Vec2 getVecWithDirAndSize(float dir, float size) { return Vec2(size*Math::Cos(dir), size*Math::Sin(dir)); }
		static inline Vec2 getVecWithDir(float dir) { return getVecWithDirAndSize(dir, 1); }
	};
}