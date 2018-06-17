#include"Engine.h"

#include"Camera.h"
#include"System.h"
#include"SceneManager.h"
#include"Mouse.h"
#include"Keyboard.h"

namespace gasolinn
{
	
	int Engine::On(std::string title, int width, int height, int win_state)
	{
		System::Init(title,width,height,win_state);

		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		setlocale(LC_ALL, "");
		TTF_Init();
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

		Camera::Init(System::width, System::height);

		Math::CreateTable();

		return 0;
	}

	int Engine::On(std::string title, Size size, Uint32 win_state)
	{
		return On(title, size.width, size.height, win_state);
	}

	int Engine::On(std::string title, int width, int height)
	{
		return On(title, width, height, SDL_WINDOW_RESIZABLE);
	}

	int Engine::On(std::string title, Size size)
	{
		return On(title, size.width, size.height, SDL_WINDOW_RESIZABLE);
	}


	int Engine::Run()
	{
		int fpsCalcCount = 0;
		unsigned long long fpsCalcTick = 0;
		unsigned long long oldTick = 0;
		unsigned long long nowTick = 0;

		while (!System::exit)
		{
			nowTick = SDL_GetTicks();
			if (oldTick == 0) oldTick = nowTick;

			if (nowTick >= oldTick + 1000.0 / (float)System::setfps)
			{
				oldTick += 1000.0 / (float)System::setfps;

				fpsCalcCount++;
				if (fpsCalcCount >= 10)
				{
					System::fps = 1000.0 * (float)fpsCalcCount / (float)(nowTick - fpsCalcTick);
					fpsCalcTick = nowTick;
					fpsCalcCount = 0;
				}
				if (!SceneManager::currentScene->isPause || !System::isWindowActivate)
					System::tick += 1;




				Mouse::wheelX = Mouse::wheelY = 0;
				Keyboard::Read();
				Mouse::Update();


				if (SDL_PollEvent(&System::event))
				{
					if (System::event.type == SDL_QUIT)
						System::exit = true;

					if (System::focusActive && System::event.type == SDL_WINDOWEVENT)
					{
						if (System::event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
							System::isWindowActivate = true;
						if (System::event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
							System::isWindowActivate = false;
					}
					if (System::event.type == SDL_MOUSEBUTTONDOWN)
					{
						if (System::event.button.button == SDL_BUTTON_LEFT) Mouse::left = true;
						if (System::event.button.button == SDL_BUTTON_RIGHT) Mouse::right = true;
						if (System::event.button.button == SDL_BUTTON_MIDDLE) Mouse::middle = true;

					}
					if (System::event.type == SDL_MOUSEBUTTONUP)
					{
						if (System::event.button.button == SDL_BUTTON_LEFT) Mouse::left = false;
						if (System::event.button.button == SDL_BUTTON_RIGHT) Mouse::right = false;
						if (System::event.button.button == SDL_BUTTON_MIDDLE) Mouse::middle = false;
					}
					if (System::event.type == SDL_MOUSEWHEEL)
					{
						Mouse::wheelX = System::event.wheel.x;
						Mouse::wheelY = System::event.wheel.y;
					}
				}
				SDL_FlushEvent(SDL_MOUSEWHEEL);

				SDL_SetRenderTarget(System::renderer, System::buffer);

				SDL_SetRenderDrawColor(System::renderer, 0, 0, 0, 255);
				SDL_RenderClear(System::renderer);
				SDL_SetRenderDrawColor(System::renderer, 255, 255, 255, 255);

				if (SceneManager::sceneChanged) SceneManager::previousScene->Background();
				SceneManager::currentScene->Background();

				SDL_SetRenderTarget(System::renderer, NULL);

				SDL_SetRenderDrawColor(System::renderer, 0, 0, 0, 255);
				SDL_RenderClear(System::renderer);
				SDL_SetRenderDrawColor(System::renderer, 255, 255, 255, 255);

				SDL_RenderCopyEx(System::renderer, System::buffer, &Camera::src, &Camera::dst, Camera::angle, &Camera::center, SDL_FLIP_NONE);

				SDL_RenderPresent(System::renderer);
			}
		}

		Release();

		return 0;
	}

	void Engine::Release()
	{
		System::Release();
		SceneManager::Release();
		ResourceManager::Release();

		SDL_Quit();
		TTF_Quit();
		Mix_CloseAudio();
	}

};