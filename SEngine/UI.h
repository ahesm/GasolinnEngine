#pragma once

#include"Structs.h"
#include"Object.h"
#include"Mouse.h"
#include"Panel.h"

using namespace gasolinn;

namespace ui
{
	class UI
	{
	public:
		UI() {};
	public:
		Ver2	pos;
		Size	size;
		Object*	parent;

		friend class Panel;
	private:
		bool	focused;
	public:
		bool Up(MouseCode mcode);
		bool Down(MouseCode mcode);
		bool Click(MouseCode mcode);
		bool Leave(MouseCode mcode);

	public:
		virtual void Update() {};
		virtual void Draw() {};
		virtual void Release() {};

		friend class Panel;
	protected:
		virtual void DrawOnPanel(Ver2 pos) {};
	};
}