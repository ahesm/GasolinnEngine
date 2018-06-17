#include"Object.h"

#include"Scene.h"
#include"SceneManager.h"
#include"System.h"
#include"Math.h"
#include"Camera.h"
#include"KeyEvent.h"


#include<thread>


namespace gasolinn
{
	void Object::Background()
	{	
		Draw();

		if (!parent->isPause && System::isWindowActivate)
		{
			if (SceneManager::sceneChanged)
			{
				if (SceneManager::currentScene == parent)
				{
					SceneManager::sceneChanged = SceneManager::currentScene->Loading(SceneManager::previousScene);
					if (!SceneManager::sceneChanged)
					{
						SceneManager::previousScene->ReleaseScene();
						SceneManager::currentScene->Initialize();
					}
				}
			}
			else 
			{
				pos.x += vector.x;
				pos.y += vector.y;
				Step();
			}
		}
	}

	void Object::ReleaseObject()
	{
		Release();

		isRelease = true;
	}

	void Object::DrawTexturePart(Texture *texture, float x, float y, int left, int top, int width, int height, int r, int g, int b)
	{
		SDL_Rect src, dst;
		SDL_Point point;

		point.x = texture->centerX*width*texture->scaleX * Camera::zoom;
		point.y = texture->centerY*height*texture->scaleY * Camera::zoom;

		src.x = left;
		src.y = top;
		src.w = width;
		src.h = height;

		dst.x = round((x - Camera::x)*Camera::zoom + Camera::x - point.x - (Camera::x - System::width / 2) + parent->x);
		dst.y = round((y - Camera::y)*Camera::zoom + Camera::y - point.y - (Camera::y - System::height / 2) + parent->y);
		dst.w = src.w * texture->scaleX * Camera::zoom;
		dst.h = src.h * texture->scaleY * Camera::zoom;

		SDL_SetTextureColorMod(texture->texture, r, g, b);
		SDL_SetTextureBlendMode(texture->texture, (SDL_BlendMode)texture->blendmode);
		SDL_SetTextureAlphaMod(texture->texture, texture->alpha*255.0);

		SDL_RenderCopyEx(System::renderer, texture->texture, &src, &dst, texture->angle, &point, SDL_FLIP_NONE);
	}

	void Object::DrawTexturePart(Texture *texture, float x, float y, int left, int top, int width, int height)
	{
		DrawTexturePart(texture, x, y, left, top, width, height, texture->r, texture->g, texture->b);
	}

	void Object::DrawTexturePart(Texture *texture, Ver2 ver, Rect rect)
	{
		DrawTexturePart(texture, ver.x, ver.y, rect.x, rect.y, rect.w, rect.h, texture->r,texture->g,texture->b);
	}


	void Object::DrawTexture(Texture *texture, float x, float y)
	{
		DrawTexturePart(texture, x, y, 0, 0, texture->size.width, texture->size.height);
	}

	void Object::DrawTexture(Texture *texture, Ver2 ver)
	{
		DrawTexture(texture, ver.x, ver.y);
	}

	void Object::DrawTexture(Texture *texture)
	{
		DrawTexture(texture, pos.x,pos.y);
	}


	int Object::DrawNumber(Texture *texture, int number, int space, float x, float y, int align)
	{
		int numlen = strlen(std::to_string(number).data());

		int w = texture->size.width / 10;
		int h = texture->size.height;

		float skv_m = w + space;//(space*(numlen - 1)) - (space*(numlen / 2));

		int skv_k = 1;

		for (int i = numlen - 1; i >= 0; i--) {
			int div = floor(number / skv_k);
			div %= 10;
			int a;
			switch (align) {
			case 0: a = i*skv_m - 1; break;
			case 1: a = i*skv_m - ((numlen) / 2)*skv_m + (1 - numlen % 2)*skv_m / 2 - 1; break;
			case 2: a = i*skv_m - (numlen - 1)*skv_m - 1; break;
			}

			DrawTexturePart(texture, x + a, y, div*w, 0, w, h, 255, 255, 255);
			skv_k *= 10;
		}
		return numlen;
	}
}