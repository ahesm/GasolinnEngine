#include "UI.h"

#include"Collision.h"
#include"Scene.h"


namespace ui
{
	bool UI::Up(MouseCode mcode)
	{
		if (focused && Mouse::Up(mcode))
		{
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
				pos.x, pos.y, size.width, size.height))
				return true;
		}
		return false;
	}

	bool UI::Down(MouseCode mcode)
	{
		if (focused && Mouse::Down(mcode))
		{
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
				pos.x, pos.y, size.width, size.height))
				return true;
		}
		return false;
	}

	bool UI::Leave(MouseCode mcode)
	{
		if (focused && Mouse::Leave(mcode))
		{
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
				pos.x, pos.y, size.width, size.height))
				return true;
		}
		return false;
	}

	bool UI::Click(MouseCode mcode)
	{
		if (focused && Mouse::Click(mcode))
		{
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
				pos.x, pos.y, size.width, size.height))
				return true;
		}
		return false;
		
	}

}