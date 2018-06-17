#pragma once

namespace gasolinn
{
	typedef enum MouseCode {
		MOUSE_LEFT, MOUSE_RIGHT, MOUSE_WHEEL
	}MouseCode;

	class Mouse
	{
		friend class Engine;
	private:
		static bool	left;
		static bool	right;
		static bool	middle;

		static bool isclick[3];

		static unsigned long long clickedTick[3];
		static unsigned long long leftTick[3];
	public:
		static int	wheelX, wheelY;

	public:
		static void Update();

		static bool Down(MouseCode mcode);
		static bool Up(MouseCode mcode);
		static bool Click(MouseCode mcode);
		static bool Leave(MouseCode mcode);
	};
}