#include"System.h"

#pragma comment(lib,"SDL2")
#pragma comment(lib,"SDL2_image")
#pragma comment(lib,"SDL2_mixer")
#pragma comment(lib,"SDL2_ttf")

namespace gasolinn
{
	SDL_Renderer*	System::renderer;
	SDL_Window*		System::window;
	SDL_Texture*	System::buffer;
	SDL_Event		System::event;

	bool			System::focusActive;
	bool			System::isWindowActivate;
	bool			System::exit;
					
	int				System::width, System::height;

	int				System::setfps;
	float			System::fps;
	unsigned long long System::tick;


	void System::Init(std::string title, int width, int height, int win_state)
	{
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			width, height, win_state);
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR4444,SDL_TEXTUREACCESS_TARGET, width, height);

		System::width = width;
		System::height = height;

		focusActive = true;
		isWindowActivate = true;
		exit = false;

		setfps = 60;
		fps = 60.0;
		tick = 0;
	}

	void System::SetFPS(int fps)
	{
		setfps = fps;
	}

	void System::Release()
	{
		if (window != nullptr) 
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}
		if (renderer != nullptr)
		{
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
		}
		if (buffer != nullptr)
		{
			SDL_DestroyTexture(buffer);
			buffer = nullptr;
		}
	}

};