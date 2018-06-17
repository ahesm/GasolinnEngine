#pragma once

#include<SDL.h>
#include<unordered_map>
#include<string>
#include<SDL_ttf.h>

#include"Structs.h"


using namespace std;

namespace gasolinn
{
	class Texture;

	typedef unordered_map<string, SDL_Texture*> SDLTextureMap;
	typedef unordered_map<string, string>		FontMap;

	typedef unordered_map<int, Texture*> TextureMap;

	class ResourceManager
	{
	public:
		static SDLTextureMap	textureMap;
		static FontMap			fontMap;
	public:
		static void Release();

		static void LoadTexture(const string& src);
		static void LoadTextures();
		static void LoadTextures(const string& src);

		static void ReleaseTexture(const string& src);
		static void ReleaseTextures();
		static void ReleaseTextures(const string& src);

		static void LoadFont(const string& src);
		static void LoadFonts();
		static void LoadFonts(const string& src);

		static void ReleaseFont(const string& src);
		static void ReleaseFonts();
		static void ReleaseFonts(const string& src);

	public:
		static Texture* GetTexture(const string& tag);
		//라벨을 쓸때만 사용!
		static TTF_Font* GetFont(const string& tag,int size);

	public:
		static TextureMap	textureGarbage;
		static void ClearGarbage();

	private:
		static int			assignGTextureId;
	};
	typedef ResourceManager RM;
}