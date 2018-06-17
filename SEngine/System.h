#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include<string>

namespace gasolinn
{
	class System
	{
	public:
		static SDL_Window*		window;
		static SDL_Renderer*	renderer;
		static SDL_Texture*		buffer;
		static SDL_Event		event;

		static bool				focusActive;
		static bool				isWindowActivate;
		static bool				exit;
		
		static int				width, height;

		static int				setfps;
		static float			fps;
		static unsigned long long tick;

	public:
		static void Init(std::string title, int width, int height, int win_state);
		static void SetFPS(int fps);
		static void Release();

	};
};