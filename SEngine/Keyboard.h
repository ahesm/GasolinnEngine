#pragma once

#include<SDL.h>

namespace gasolinn
{
	class Keyboard
	{
	public:
		static const Uint8*	keyState;

	public:
		static void Release();

	public:
		static void Read();

	public:
		static bool Down(unsigned char keycode);
		static bool Up(unsigned char keycode);
	};
}