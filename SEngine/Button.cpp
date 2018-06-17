#include"Button.h"

#include"Collision.h"
#include"Scene.h"
#include"Camera.h"
#include"System.h"

namespace ui
{
	Button * Button::Create(Object *parent, Texture *btn, Texture *on, Texture *down, Ver2 pos)
	{
		Button *button = new Button;
		button->parent = parent;
		button->button = btn;
		button->buttonOn = on;
		button->buttonDown = down;
		button->pos = pos;
		button->size = btn->size;
		return button;
	}

	Button * Button::Create(Object *parent, Texture *btn, Texture *on, Texture *down, float x, float y)
	{
		return Create(parent, btn, on, down, Ver2(x, y));
	}
	
	void Button::Update()
	{
		if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
			pos.x, pos.y, size.width, size.height))
		{
			mouseOn = true;
			mouseDown = false;
			if (Mouse::Down(MOUSE_LEFT))
			{
				mouseDown = true;
			}
		}
		else
		{
			mouseOn = false;
			mouseDown = false;
		}
	}
	
	void Button::Draw()
	{
		if (mouseOn && !mouseDown)DrawTexture(buttonOn, pos, Camera::x, Camera::y, Camera::zoom);
		else if (mouseDown)DrawTexture(buttonDown, pos, Camera::x, Camera::y, Camera::zoom);
		else DrawTexture(button, pos, Camera::x, Camera::y, Camera::zoom);
	}

	void Button::DrawOnPanel(Ver2 pos)
	{
		if (mouseOn && !mouseDown)DrawTexture(buttonOn, pos, System::width / 2, System::height / 2, 1);
		else if (mouseDown)DrawTexture(buttonDown, pos, System::width / 2, System::height / 2, 1);
		else DrawTexture(button, pos, System::width / 2, System::height / 2, 1);
	}

	void Button::DrawTexture(Texture * texture, Ver2 pos, float cameraX, float cameraY, float zoom)
	{
		SDL_Rect src, dst;
		SDL_Point point;

		point.x = texture->centerX*size.width * texture->scaleX * zoom;
		point.y = texture->centerY*size.height * texture->scaleY * zoom;

		src.x = 0;
		src.y = 0;
		src.w = texture->size.width;
		src.h = texture->size.height;

		dst.x = round((pos.x - cameraX)*zoom + cameraX - point.x - (cameraX - System::width / 2) + parent->parent->x);
		dst.y = round((pos.y - cameraY)*zoom + cameraY - point.y - (cameraY - System::height / 2) + parent->parent->y);
		dst.w = texture->size.width * texture->scaleX * zoom;
		dst.h = texture->size.height * texture->scaleY * zoom;

		SDL_SetTextureColorMod(texture->texture, texture->r, texture->g, texture->b);
		SDL_SetTextureBlendMode(texture->texture, (SDL_BlendMode)texture->blendmode);
		SDL_SetTextureAlphaMod(texture->texture, texture->alpha*255.0);

		SDL_RenderCopyEx(System::renderer, texture->texture, &src, &dst, texture->angle, &point, SDL_FLIP_NONE);
	}
	
	void Button::Release()
	{
		if (button != nullptr)
		{
			delete button;
			button == nullptr;
		}
		if (buttonOn != nullptr)
		{
			delete buttonOn;
			buttonOn == nullptr;
		}
		if (buttonDown != nullptr)
		{
			delete buttonDown;
			buttonDown == nullptr;
		}
		delete this;
	}
}