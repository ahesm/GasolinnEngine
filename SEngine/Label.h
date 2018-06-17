#pragma once

#include<SDL.h>
#include<SDL_ttf.h>
#include<string>

#include"Texture.h"
#include"Vector.h"
#include"Object.h"
#include"UI.h"

using namespace gfunc;
using namespace gasolinn;

//줄바꿈 만들자!

namespace ui
{
	class Label : public UI
	{
	public:
		Label() {};
	private:
		TTF_Font*		font;
		std::wstring	text;

		SDL_Texture*	texture;
	public:
		float			centerX = 0.5, centerY = 0.5;
		float			scaleX = 1.0, scaleY = 1.0;
		float			alpha = 1;
		float			angle = 0;
		BlendMode		blendmode = BLENDMODE_BLEND;

	private:
		bool			isFirst = true;

		bool			isShadow = false;
		float			shadowAngle = 0;

		int				r = 0, g = 0, b = 0;
		SDL_Color		shadowColor;
	public:
		static Label *Create(Object *parent, TTF_Font *font, Ver2 pos);
		static Label *Create(Object *parent, TTF_Font *font, float x, float y);

		static const Size CalcText(TTF_Font *font, const std::wstring &text);

		void SetText(const std::wstring &text);
		/*만약 글이 박스를 넘어서면 -1 반환, 평소엔 0 반환*/
		int SetTextInBox(const std::wstring &text, int width, int height);

		void SetScale(float scaleX, float scaleY);
		void SetCenter(float centerX, float centerY);
		void SetColor(int r, int g, int b);
		void SetShadow(float angle, int r, int g, int b);

		void Draw();
		void Release();

	protected:
		void DrawOnPanel(Ver2 pos);

	private:
		void DrawText(SDL_Texture *texture, float x, float y, float centerX, float centerY, float angle, float alpha, BlendMode blendmode, int r, int g, int b, float cameraX,float cameraY,float zoom);
		static Uint16 *WCharToUint16(std::wstring text);
	};
}

