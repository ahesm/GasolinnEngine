#include"Keyboard.h"

namespace gasolinn
{
	const Uint8* Keyboard::keyState = 0;

	void Keyboard::Read()
	{
		keyState = SDL_GetKeyboardState(NULL);
	}

	bool Keyboard::Down(unsigned char keycode)
	{
		if (keyState[keycode])
			return true;
		return false;
	}

	bool Keyboard::Up(unsigned char keycode)
	{
		if (!keyState[keycode])
			return true;
		return false;
	}

	void Keyboard::Release()
	{
		SDL_free(&keyState);
	}

}