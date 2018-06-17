#pragma once

#include"UI.h"

namespace ui
{
	class Slider : public UI
	{
	public:
		Texture*	line;
		Texture*	coloredLine;
		Texture*	slider;

		float		sliderX;

	private:
		bool		sliding;
	public:
		static Slider* Create(Object *parent,Ver2 pos, Texture *slider,Texture *line,Texture *coloredLine);
		
	public:
		void Update();
		void Draw();
		void Release();
		void DrawOnPanel(Ver2 pos);

	private:
		void DrawTexture(Texture * texture, Ver2 pos, float cameraX, float cameraY, float zoom);
		void DrawTexturePart(Texture * texture,Ver2 pos, int left, int top  ,int width,int height, float cameraX, float cameraY, float zoom);
	};
}