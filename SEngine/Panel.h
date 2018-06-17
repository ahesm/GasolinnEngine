#pragma once

#include"Structs.h"
#include<vector>
#include"Object.h"

using namespace gasolinn;

//개발필요

namespace ui
{
	class UI;
	class Panel
	{
	public:
		Panel() {};
	public:
		Ver2				pos;
		Size				size;
		Size				extendedSize;
		Size				rSize;

		int					vscrPos = 0, hscrPos = 0;
		Ver2				scrollPos;

		bool				vScroll = false, hScroll = false;


		bool				focused = false;
		
		std::vector<UI*>	uiMap;

		Object*				parent;
	private:
		SDL_Texture*		buffer;
		Texture*			scrollbar;
		Texture*			head;
		Texture*			vBody;
		Texture*			hBody;

	private:
		float				drawScrIntervalX;
		float				drawScrIntervalY;
		Size				scrollSize;

		bool vScrollPressing;
		bool hScrollPressing;

	public:
		static Panel* Create(Object *parent, Ver2 pos, Size size);
		static Panel* Create(Object *parent, Ver2 pos, Size size, bool vScroll, bool hScroll, Texture* scrollbar, Texture* head);
		void Add(UI *ui);

	public:
		void Update();
		void Draw();
		void Release();
	private:
		void DrawTexture(Texture *texture, Ver2 pos, float angle);
		

	};
}