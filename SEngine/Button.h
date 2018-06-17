#pragma once

#include"Object.h"
#include"ResourceManager.h"
#include"Texture.h"
#include"UI.h"

using namespace gasolinn;
namespace ui
{
	class Button : public UI
	{
	public:
		Button() {};
	private:
		Texture*		button;
		Texture*		buttonDown;
		Texture*		buttonOn;

		bool			mouseOn = false;
		bool			mouseDown = false;
	public:
		static Button *Create(Object *parent, Texture *btn, Texture *on, Texture *down, Ver2 pos);
		static Button *Create(Object *parent, Texture *btn, Texture *on, Texture *down, float x, float y);

		void Update();
		void Draw();
		void DrawTexture(Texture *texture, Ver2 pos, float cameraX, float cameraY, float zoom);
		void Release();

	protected:
		void DrawOnPanel(Ver2 pos);
	};
}

