#include"Slider.h"

#include"System.h"
#include"Collision.h"
#include"Scene.h"
#include"Camera.h"

namespace ui
{
	Slider * Slider::Create(Object * parent, Ver2 pos, Texture * slider, Texture * line, Texture * coloredLine)
	{
		Slider *sli = new Slider;
		sli->parent = parent;
		sli->pos = pos;
		sli->slider = slider;
		sli->line = line;
		sli->coloredLine = coloredLine;
		sli->size = line->size;
		sli->sliding = false;

		sli->coloredLine->SetCenter(0, 0);
		return sli;
	}

	void Slider::Update()
	{
		int zeroPoint = pos.x - size.width / 2;
		int mousePoint = parent->parent->mouse.x;
		if (Mouse::Click(MOUSE_LEFT))
		{
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
				pos.x, pos.y, line->size.width, line->size.height))
			{
				sliderX = (float)(mousePoint - zeroPoint) / (float)size.width;
			}
			if (Collision::PointToRect(parent->parent->mouse.x, parent->parent->mouse.y,
				zeroPoint + sliderX*size.width, pos.y, slider->size.width, slider->size.height))
			{
				sliding = true;
			}
		}
		if (Mouse::Leave(MOUSE_LEFT))
		{
			if (sliding) sliding = false;
		}
		if (sliding)
		{
			sliderX = (float)(mousePoint - zeroPoint) / (float)size.width;
			if (sliderX > 1)sliderX = 1;
			if (sliderX < 0) sliderX = 0;
		}
	}

	void Slider::Draw()
	{
		DrawTexture(line, pos, Camera::x, Camera::y, Camera::zoom);
		DrawTexturePart(coloredLine,pos-Ver2(coloredLine->size.width/2,coloredLine->size.height/2), 0,0, sliderX*size.width, coloredLine->size.height, Camera::x, Camera::y, Camera::zoom);
		DrawTexture(slider, Ver2(sliderX*size.width + pos.x - size.width / 2, pos.y), Camera::x, Camera::y, Camera::zoom);
	}

	void Slider::Release()
	{
		if (line != nullptr)
		{
			delete line;
			line = nullptr;
		}
		if (coloredLine != nullptr)
		{
			delete coloredLine;
			coloredLine = nullptr;
		}
		if (slider != nullptr)
		{
			delete slider;
			slider = nullptr;
		}
		delete this;
	}

	void Slider::DrawOnPanel(Ver2 pos)
	{
		DrawTexture(line, pos, System::width/2,System::height/2,1);
		DrawTexturePart(coloredLine,pos,pos.x-coloredLine->size.width/2,pos.y-coloredLine->size.height/2, sliderX*size.width, coloredLine->size.height, System::width / 2, System::height / 2, 1);
		DrawTexture(slider, Ver2(sliderX*size.width + pos.x - size.width / 2, pos.y), System::width / 2, System::height / 2, 1);
	}

	void Slider::DrawTexture(Texture * texture, Ver2 pos, float cameraX, float cameraY, float zoom)
	{
		SDL_Rect src, dst;
		SDL_Point point;

		point.x = texture->centerX*texture->size.width * texture->scaleX * zoom;
		point.y = texture->centerY*texture->size.height * texture->scaleY * zoom;

		src.x = 0;
		src.y = 0;
		src.w = texture->size.width;
		src.h = texture->size.height;

		dst.x = round((pos.x - cameraX)*zoom + cameraX - point.x - (cameraX - System::width / 2) + parent->parent->x);
		dst.y = round((pos.y - cameraY)*zoom + cameraY - point.y - (cameraY - System::height / 2) + parent->parent->y);
		dst.w = src.w * texture->scaleX * zoom;
		dst.h = src.h * texture->scaleY * zoom;

		SDL_SetTextureColorMod(texture->texture, texture->r, texture->g, texture->b);
		SDL_SetTextureBlendMode(texture->texture, (SDL_BlendMode)texture->blendmode);
		SDL_SetTextureAlphaMod(texture->texture, texture->alpha*255.0);

		SDL_RenderCopyEx(System::renderer, texture->texture, &src, &dst, texture->angle, &point, SDL_FLIP_NONE);
	}

	void Slider::DrawTexturePart(Texture * texture,Ver2 pos, int left,int top,int width,int height, float cameraX, float cameraY, float zoom)
	{
		SDL_Rect src, dst;
		SDL_Point point;

		point.x = texture->centerX*width * texture->scaleX * zoom;
		point.y = texture->centerY*height * texture->scaleY * zoom;

		src.x = left;
		src.y = top;
		src.w = width;
		src.h = height;

		dst.x = round((pos.x - cameraX)*zoom + cameraX - point.x - (cameraX - System::width / 2) + parent->parent->x);
		dst.y = round((pos.y - cameraY)*zoom + cameraY - point.y - (cameraY - System::height / 2) + parent->parent->y);
		dst.w = src.w * texture->scaleX * zoom;
		dst.h = src.h * texture->scaleY * zoom;

		SDL_SetTextureColorMod(texture->texture, texture->r, texture->g, texture->b);
		SDL_SetTextureBlendMode(texture->texture, (SDL_BlendMode)texture->blendmode);
		SDL_SetTextureAlphaMod(texture->texture, texture->alpha*255.0);

		SDL_RenderCopyEx(System::renderer, texture->texture, &src, &dst, texture->angle, &point, SDL_FLIP_NONE);
	}

}