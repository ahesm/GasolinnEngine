#include "KeyEvent.h"

#include "Keyboard.h"

#include "Timer.h"
#include "Scene.h"

#include<stdarg.h>

namespace gasolinn
{

	KeyEvent *KeyEvent::Create(unsigned char firstkey,...)
	{
		auto ke = new KeyEvent;

		auto key = new Key;
		key->flag = false;
		key->timer = Timer::Create();
		ke->keys.insert(std::make_pair(firstkey, key));

		va_list args;

		va_start(args, firstkey);
		
		unsigned char keycode = va_arg(args, unsigned char);
		while (keycode)
		{
			auto key = new Key;
			key->flag = false;
			key->timer = Timer::Create();
			ke->keys.insert(std::make_pair(keycode,key));
			keycode = va_arg(args, unsigned char);
		} 

		va_end(args);

		return ke;
	}

	bool KeyEvent::GetKeyPressed(unsigned char keycode)
	{
		if (Keyboard::Down(keycode) && !keys[keycode]->flag) {
			keys[keycode]->flag = true;
			return true;
		}

		if (Keyboard::Up(keycode)) {
			keys[keycode]->flag = false;
		}

		return false;
	}

	bool KeyEvent::GetKeyDelay(unsigned char keycode, unsigned int fDelay, unsigned int mDelay)
	{
		/// 키 처음 눌렀을때
		if (Keyboard::Down(keycode) && !keys[keycode]->firstFlag) {
			keys[keycode]->tickOn = true;
			keys[keycode]->firstFlag = true;
			return true;
		}

		if (Keyboard::Up(keycode)) {
			keys[keycode]->tickOn = false;
			keys[keycode]->moveOn = false;
			keys[keycode]->firstFlag = false;
			keys[keycode]->tick = 0;
		}

		if (keys[keycode]->tickOn) {
			keys[keycode]->tick += 1;
			if (keys[keycode]->tick >= fDelay) {
				keys[keycode]->moveOn = true;
			}
		}

		if (keys[keycode]->moveOn) {
			if (keys[keycode]->timer->Tick(mDelay))
				return true;
			return false;
		}

		return false;
	}

	void KeyEvent::Release()
	{
		for (auto iter = keys.begin(); iter != keys.end();)
		{
			(*iter).second->timer->Release();
			if((*iter).second != nullptr)
				delete (*iter).second;
		}
		keys.clear();
		std::unordered_map<unsigned char, Key*>().swap(keys);

		delete this;
	}
}