#pragma once

#include"Structs.h"
#include"ResourceManager.h"


namespace gasolinn
{
	typedef enum _BlendMode {
		BLENDMODE_NONE = 0, BLENDMODE_BLEND = 1, BLENDMODE_ADD = 2, BLENDMODE_MOD = 3
	}BlendMode;

	class Texture
	{
	public:
		Texture() {};
	public:
		SDL_Texture*	texture;
		BlendMode		blendmode;
		Size			size;
		int				r, g, b;
		float			angle;
		float			alpha;
		float			scaleX, scaleY;
		float			centerX, centerY;

		friend class ResourceManager;
	private:
		bool			inRM;
		int				id;

	public:
		void Init(float angle, float alpha, int r, int g, int b, float scaleX, float scaleY, float centerX, float centerY, BlendMode blendmode)
		{
			this->angle = angle; this->alpha = alpha;
			this->r = r; this->g = g; this->b = b;
			this->scaleX = scaleX; this->scaleY = scaleY;
			this->centerX = centerX; this->centerY = centerY;
			this->blendmode = blendmode;
		};
		inline void SetRGB(int r, int g, int b) { this->r = r; this->g = g; this->b = b; }
		inline void SetScale(float scaleX, float scaleY) { this->scaleX = scaleX; this->scaleY = scaleY; };
		inline void SetCenter(float centerX, float centerY) { this->centerX = centerX; this->centerY = centerY; };

		void Release() 
		{
			if (!inRM && texture != nullptr) SDL_DestroyTexture(texture);
			ResourceManager::textureGarbage[id] = nullptr;
			delete this; 
		};

	public:
		static Texture** SplitTextureWithWidth(Texture *texture, int width);
		static Texture** SplitTextureWithHeight(Texture *texture, int height);
		static Texture* ResizeTexture(Texture *texture, Size size);



	};
}