#pragma once

#include<SDL.h>

#include"Structs.h"

//CAMERA SRC DST ±¸Çö

namespace gasolinn
{
	class Camera
	{
	public:
		static float	 x, y;
		static float	 zoom;
		static Rect		 rect;
		//not yet
		static float	 angle;

		static float	 leftEnd;
		static float	 rightEnd;
		static float	 topEnd;
		static float	 bottomEnd;


	friend class Engine;
	private:
		static SDL_Rect  src, dst;
		static SDL_Point center;

	public:
		static void Init(int width, int height);
		static void Update();
	};
}