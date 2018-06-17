#include"Texture.h"

#include<stdio.h>
#include"System.h"

namespace gasolinn
{
	Texture ** Texture::SplitTextureWithWidth(Texture * texture, int width)
	{
		if (texture == nullptr)
		{
			return nullptr;
		}
		Texture **tArr = new Texture*[2];

		tArr[0]->texture = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, width, texture->size.height);
		tArr[1]->texture = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, texture->size.width - width, texture->size.height);

		SDL_SetRenderTarget(System::renderer, tArr[0]->texture);

		SDL_Rect src, dst;

		src.x = src.y = 0;
		src.w = width;
		src.h = texture->size.height;

		dst.x = dst.y = 0;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(System::renderer, texture->texture, &src, &dst);

		tArr[0]->Init(0, 1.0f, 255, 255, 255, 1.0f, 1.0f, 0.5f, 0.5f, BLENDMODE_BLEND);
		tArr[0]->size = Size(src.w, src.h);

		SDL_SetRenderTarget(System::renderer, tArr[1]->texture);

		src.x = width;
		src.y = 0;
		src.w = texture->size.width - width;
		src.h = texture->size.height;

		dst.x = dst.y = 0;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(System::renderer, texture->texture, &src, &dst);

		SDL_SetRenderTarget(System::renderer, System::buffer);

		tArr[1]->Init(0, 1.0f, 255, 255, 255, 1.0f, 1.0f, 0.5f, 0.5f, BLENDMODE_BLEND);
		tArr[1]->size = Size(src.w, src.h);

		return tArr;
	}

	Texture ** Texture::SplitTextureWithHeight(Texture * texture, int height)
	{
		if (texture == nullptr)
		{
			return nullptr;
		}
		Texture **tArr = new Texture*[2];
		tArr[0] = new Texture;
		tArr[1] = new Texture;
		tArr[0]->inRM = false;
		tArr[1]->inRM = false;

		tArr[0]->texture = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, texture->size.width, height);
		tArr[1]->texture = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, texture->size.width, texture->size.height - height);

		SDL_SetRenderTarget(System::renderer, tArr[0]->texture);

		SDL_Rect src, dst;

		src.x = src.y = 0;
		src.w = texture->size.width;
		src.h = height;

		dst.x = dst.y = 0;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(System::renderer, texture->texture, &src, &dst);

		tArr[0]->Init(0, 1.0f, 255, 255, 255, 1.0f, 1.0f, 0.5f, 0.5f, BLENDMODE_BLEND);
		tArr[0]->size = Size(src.w, src.h);

		SDL_SetRenderTarget(System::renderer, tArr[1]->texture);

		src.x = 0;
		src.y = height;
		src.w = texture->size.width;
		src.h = texture->size.height - height;

		dst.x = dst.y = 0;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(System::renderer, texture->texture, &src, &dst);

		SDL_SetRenderTarget(System::renderer, System::buffer);

		tArr[1]->Init(0, 1.0f, 255, 255, 255, 1.0f, 1.0f, 0.5f, 0.5f, BLENDMODE_BLEND);
		tArr[1]->size = Size(src.w, src.h);

		return tArr;
	}

	Texture * Texture::ResizeTexture(Texture * texture, Size size)
	{
		if (texture == nullptr)
		{
			return nullptr;
		}
		Texture *resizedTexture = new Texture;
		resizedTexture->Init(0, 1.0f, 255, 255, 255, 1.0f, 1.0f, 0.5f, 0.5f, BLENDMODE_BLEND);
		resizedTexture->size = size;
		resizedTexture->inRM = false;
		resizedTexture->texture = SDL_CreateTexture(System::renderer, SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_TARGET, size.width, size.height);

		SDL_Rect src, dst;
		src.x = src.y = 0;
		src.w = texture->size.width;
		src.h = texture->size.height;

		dst.x = dst.y = 0;
		dst.w = size.width;
		dst.h = size.height;

		SDL_SetRenderTarget(System::renderer, resizedTexture->texture);

		SDL_RenderCopy(System::renderer, texture->texture, &src, &dst);

		SDL_SetRenderTarget(System::renderer, System::buffer);

		return resizedTexture;
	}
}