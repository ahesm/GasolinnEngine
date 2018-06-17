#include"Label.h"

#include"ResourceManager.h"
#include"Texture.h"
#include"Math.h"
#include"System.h"
#include"Structs.h"
#include"Camera.h"
#include"Scene.h"
#include<wchar.h>

using namespace gfunc;
using namespace gasolinn;

namespace ui
{
	Label *Label::Create(Object* parent,TTF_Font *font, Ver2 pos)
	{
		if (font == NULL) {
			printf("Error: no font in label");
			return NULL;
		}
		Label *label = new Label;
		label->parent = parent;
		label->font = font;
		label->pos = pos;

		return label;
	}

	Label *Label::Create(Object *parent, TTF_Font *font, float x, float y)
	{
		return Create(parent, font, Ver2(x, y));
	}

	const Size Label::CalcText(TTF_Font *font, const std::wstring &text)
	{
		Size size;
		Uint16 *utext = WCharToUint16(text);
		TTF_SizeUNICODE(font, utext, &size.width, &size.height);
		delete[] utext;
		return size;
	}
	
	void Label::SetScale(float scaleX, float scaleY)
	{
		this->scaleX = scaleX;
		this->scaleY = scaleY;
	}

	void Label::SetCenter(float centerX, float centerY)
	{
		this->centerX = centerX;
		this->centerY = centerY;
	}

	void Label::SetText(const std::wstring &text)
	{
		if (!isFirst) {
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}

		this->text = text;
		Uint16 *utext = WCharToUint16(text);
		SDL_Color color = { 255,255,255,255 };
		SDL_Surface *s_t = TTF_RenderUNICODE_Blended(font, utext, color);
		texture = SDL_CreateTextureFromSurface(System::renderer, s_t);
		SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);

		SDL_FreeSurface(s_t);
		delete[] utext;

		isFirst = false;
	}

	int Label::SetTextInBox(const std::wstring &text, int width, int height)
	{
		if (!isFirst) {
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}

		this->text = text;

		Uint16 *utext = WCharToUint16(text);
		SDL_Color color = { 255, 255, 255, 255 };
		SDL_Surface *s_t = TTF_RenderUNICODE_Blended_Wrapped(font, utext, color, width);
		SDL_Texture *tText = SDL_CreateTextureFromSurface(System::renderer, s_t);
		SDL_Texture *buffer = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, width, height);

		SDL_SetRenderTarget(System::renderer, buffer);
		DrawText(tText, width / 2, height / 2, centerX, centerY, angle, alpha, blendmode, 255, 255, 255, System::width / 2, System::height / 2, 1);
		SDL_SetRenderTarget(System::renderer, System::buffer);
		texture = tText;
		SDL_QueryTexture(texture, NULL, NULL, &size.width, &size.height);
		SDL_FreeSurface(s_t);
		delete[] utext;

		isFirst = false;
		return 0;
	}

	void Label::SetColor(int r, int g, int b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void Label::SetShadow(float angle, int r, int g, int b)
	{
		isShadow = true;
		shadowAngle = angle;
		shadowColor.r = r;
		shadowColor.g = g;
		shadowColor.b = b;
	}

	void Label::Draw()
	{
		if (isShadow)
			DrawText(texture, pos.x + 2 * Math::Cos(shadowAngle), pos.y + 2 * Math::Sin(shadowAngle), centerX, centerY, angle, alpha, blendmode, shadowColor.r, shadowColor.g, shadowColor.b,Camera::x,Camera::y,Camera::zoom);
		DrawText(texture, pos.x, pos.y, centerX, centerY, angle, alpha, blendmode, r, g, b, Camera::x, Camera::y, Camera::zoom);
	}

	void Label::DrawOnPanel(Ver2 pos)
	{
		if (isShadow)
			DrawText(texture, pos.x + 2 * Math::Cos(shadowAngle), pos.y + 2 * Math::Sin(shadowAngle), centerX, centerY, angle, alpha, blendmode, shadowColor.r, shadowColor.g, shadowColor.b, System::width / 2, System::height / 2, 1.0);
		DrawText(texture, pos.x, pos.y, centerX, centerY, angle, alpha, blendmode, r, g, b, System::width / 2, System::height / 2, 1.0);
	}


	void Label::DrawText(SDL_Texture *texture, float x, float y, float centerX, float centerY, float angle, float alpha, BlendMode blendmode, int r, int g, int b, float cameraX,float cameraY,float zoom)
	{
		SDL_Rect src, dst;
		SDL_Point point;

		point.x = centerX*size.width * scaleX * zoom;
		point.y = centerY*size.height * scaleY * zoom;

		src.x = 0;
		src.y = 0;
		src.w = size.width;
		src.h = size.height;

		dst.x = round((x - cameraX)*zoom + x - point.x - (x - System::width / 2) + parent->parent->x);
		dst.y = round((y - cameraY)*zoom + y - point.y - (y - System::height / 2) + parent->parent->y);
		dst.w = size.width * scaleX * zoom;
		dst.h = size.height * scaleY * zoom;

		SDL_SetTextureColorMod(texture, r, g, b);
		SDL_SetTextureBlendMode(texture, (SDL_BlendMode)blendmode);
		SDL_SetTextureAlphaMod(texture, alpha*255.0);

		SDL_RenderCopyEx(System::renderer, texture, &src, &dst, angle, &point, SDL_FLIP_NONE);
	}

	void Label::Release()
	{
		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
		TTF_CloseFont(font);
		delete this;
	}

	Uint16 *Label::WCharToUint16(std::wstring text)
	{
		Uint16 *utext = new Uint16[text.size() + 1];
		for (int i = 0; i < text.size(); i++) utext[i] = text[i];
		utext[text.size()] = 0;
		return utext;
	}

}