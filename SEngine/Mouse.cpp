#include"Mouse.h"

#include"System.h"

namespace gasolinn
{
	bool	Mouse::left = false;
	bool	Mouse::right = false;
	bool	Mouse::middle = false;

	bool	Mouse::isclick[3] = { false };

	unsigned long long Mouse::clickedTick[3] = { 0 };
	unsigned long long Mouse::leftTick[3] = { 0 };

	int		Mouse::wheelX = 0, Mouse::wheelY = 0;
	


	void Mouse::Update()
	{
		for (int i = 0; i < 3;i++)
		{
			MouseCode m = (MouseCode)i;
			if (Up(m)) {
				isclick[m] = false;
			}
			if (Down(m)) {
				isclick[m] = true;
			}
		}
	}

	bool Mouse::Down(MouseCode mcode)
	{
		switch (mcode)
		{
		case MOUSE_LEFT: return left;
		case MOUSE_RIGHT: return right;
		case MOUSE_WHEEL: return middle;
		}
		return false;
	}
	bool Mouse::Up(MouseCode mcode)
	{
		switch (mcode)
		{
		case MOUSE_LEFT: return !left;
		case MOUSE_RIGHT: return !right;
		case MOUSE_WHEEL: return !middle;
		}
		return false;
	}
	bool Mouse::Click(MouseCode mcode)
	{
		if (Down(mcode)) {
			if (clickedTick[mcode] == System::tick || !isclick[mcode]) {
				isclick[mcode] = true;
				clickedTick[mcode] = System::tick;
				return true;
			}
		}
		
		return false;
	}
	bool Mouse::Leave(MouseCode mcode)
	{
		if (Up(mcode)) {
			if (leftTick[mcode] == System::tick || isclick[mcode]) {
				isclick[mcode] = false;
				leftTick[mcode] = System::tick;
				return true;
			}
		}
		
		return false;
	}
}