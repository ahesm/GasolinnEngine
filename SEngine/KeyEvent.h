#pragma once

#include "Timer.h"

#include<unordered_map>

namespace gasolinn
{
	struct Key {
		bool flag = false;
		Timer *timer;
		int tick = 0;

		bool firstFlag = false;
		bool tickOn = false;
		bool moveOn = false;
	};

	class KeyEvent
	{
	private:
		std::unordered_map<unsigned char, Key*> keys;

	public:
		static KeyEvent *Create(unsigned char firstkey,...);

		bool GetKeyPressed(unsigned char keycode);

		bool GetKeyDelay(unsigned char keycode, unsigned int fDelay, unsigned int mDelay);

		void Release();
	};

}