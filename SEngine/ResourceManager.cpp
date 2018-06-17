#include"ResourceManager.h"

#include<fstream>
#include<io.h>
#include<string>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<stdio.h>

#include"System.h"
#include"String.h"
#include"Texture.h"

namespace gasolinn
{
	SDLTextureMap		ResourceManager::textureMap;
	FontMap				ResourceManager::fontMap;

	TextureMap			ResourceManager::textureGarbage;
	int					ResourceManager::assignGTextureId;

	void ResourceManager::Release()
	{
		ReleaseTextures();
		textureMap.clear();
		SDLTextureMap().swap(textureMap);
	}

	void ResourceManager::LoadTexture(const string& src)
	{
		SDL_Texture *texture = IMG_LoadTexture(System::renderer,src.c_str());
		if (texture == NULL)
		{
			printf("error: texture none, %s\n", src.c_str());
			return;
		}
		
		//string name = src.substr(src.find_last_of("\\"), src.length()-1);	
		textureMap.insert(std::make_pair(src, texture));
	}

	//리소스 암호화 추후 추가
	void ResourceManager::LoadTextures()
	{
		LoadTextures("");
	}

	void ResourceManager::LoadTextures(const string& src)
	{
		ifstream in;

		string path = "resources\\images\\" + src + "\\";

		_finddata_t fd;
		long handle = _findfirst((path + "*.*").c_str(), &fd);

		if (handle == -1) {
			printf("no image file or directory: %s\n",src);
			return;
		}

		string format[] = { "cur","ico","gif","png","bmp","jpg","lbm","pcx","pnm","tga","tif","webp","xcf","xpm","xv" };

		do
		{		
			if (!strcmp(fd.name, ".") || !strcmp(fd.name, "..") || !strcmp(fd.name, "Thumbs.db")) {
				continue;
			}
			if (fd.attrib == 0x30) {
				LoadTextures(src+"\\"+fd.name);
			}
			string *filename = gfunc::String::Split(fd.name, ".");

			for (auto ext : format)
			{
				if (filename[1].c_str() == ext)
				{
					SDL_Texture *texture = IMG_LoadTexture(System::renderer, (path + fd.name).c_str());
					if (texture == NULL)
					{
						printf("error: texture none, %s\n", (src + "\\" + fd.name).c_str());
						return;
					}
					textureMap.insert(std::make_pair(filename[0], texture));
					break;
				}
			}

		} while (_findnext(handle, &fd) != -1);

		_findclose(handle);

	}

	void ResourceManager::ReleaseTexture(const string& src)
	{

		for (auto iter = textureMap.begin(); iter != textureMap.end();)
		{
			if (iter->first == src) {
				if (iter->second != nullptr) {
					SDL_DestroyTexture(iter->second);
					iter->second = nullptr;
				}
				textureMap.erase(iter++);
			}
			else ++iter;
		}
	}

	void ResourceManager::ReleaseTextures()
	{
		ReleaseTextures("");
	}

	void ResourceManager::ReleaseTextures(const string& src)
	{
		ifstream in;

		string path = "resources\\images\\";

		_finddata_t fd;
		long handle = _findfirst((path + src + "\\*.*").c_str(), &fd);

		if (handle == -1) {
			printf("no [R] image files: %s\n", src);
			return;
		}

		string format[] = { "cur","ico","gif","png","bmp","jpg","lbm","pcx","pnm","tga","tif","webp","xcf","xpm","xv" };

		do
		{
			if (!strcmp(fd.name, ".") || !strcmp(fd.name, "..") || !strcmp(fd.name, "Thumbs.db")) {
				continue;
			}
			if (fd.attrib == 0x30) {
				ReleaseTextures(src + "\\" + fd.name);
			}
			string *filename = gfunc::String::Split(fd.name, ".");

			for (auto ext : format)
			{
				if (filename[1].c_str() == ext)
				{
					if (textureMap[filename[0]] != nullptr)
					{
						SDL_DestroyTexture(textureMap[filename[0]]);
						textureMap[filename[0]] = nullptr;
					}
					textureMap.erase(filename[0]);
					break;
				}
			}

		} while (_findnext(handle, &fd) != -1);

		//for (auto iter = textureMap.begin(); iter != textureMap.end();)
		//{
		//	if (iter->second == NULL) textureMap.erase(iter++);
		//	else ++iter;
		//}

		_findclose(handle);
	}

	void ResourceManager::LoadFont(const string & src)
	{
		if (TTF_OpenFont(src.c_str(), 10) == NULL) {
			printf("no font file, %s\n",src);
		}
		//string name = src.substr(src.find_last_of("\\"), src.length() - 1);
		fontMap.insert(std::make_pair(src, src));
	}

	void ResourceManager::LoadFonts()
	{
		LoadFonts("");
	}

	void ResourceManager::LoadFonts(const string & src)
	{
		ifstream in;

		string path = "resources\\fonts\\" + src + "\\";

		_finddata_t fd;
		long handle = _findfirst((path + "*.*").c_str(), &fd);

		if (handle == -1) {
			printf("no font file or directory: %s\n", src);
			return;
		}

		string format[] = { "ttf" };

		do
		{
			if (!strcmp(fd.name, ".") || !strcmp(fd.name, "..") || !strcmp(fd.name, "Thumbs.db")) {
				continue;
			}
			if (fd.attrib == 0x30) {
				LoadFonts(src + "\\" + fd.name);
			}
			string *filename = gfunc::String::Split(fd.name, ".");

			for (auto ext : format)
			{
				if (filename[1].c_str() == ext)
				{
					if (TTF_OpenFont((path+fd.name).c_str(), 10) == NULL) {
						printf("no font file, %s\n", filename[0]);
					}
					fontMap.insert(std::make_pair(filename[0], path + fd.name));
					break;
				}
			}

		} while (_findnext(handle, &fd) != -1);

		_findclose(handle);
	}

	void ResourceManager::ReleaseFont(const string & src)
	{
		for (auto iter = fontMap.begin(); iter != fontMap.end();)
		{
			if (iter->first == src) {
				fontMap.erase(iter++);
			}
			else ++iter;
		}
	}

	void ResourceManager::ReleaseFonts()
	{
		ReleaseFonts("");
	}

	void ResourceManager::ReleaseFonts(const string & src)
	{
		ifstream in;

		string path = "resources\\fonts\\";

		_finddata_t fd;
		long handle = _findfirst((path + src + "\\*.*").c_str(), &fd);

		if (handle == -1) {
			printf("no [R] font files: %s\n", src);
			return;
		}

		string format[] = { "ttf" };

		do
		{
			if (!strcmp(fd.name, ".") || !strcmp(fd.name, "..") || !strcmp(fd.name, "Thumbs.db")) {
				continue;
			}
			if (fd.attrib == 0x30) {
				ReleaseFonts(src + "\\" + fd.name);
			}
			string *filename = gfunc::String::Split(fd.name, ".");

			for (auto ext : format)
			{
				if (filename[1].c_str() == ext)
				{
					fontMap.erase(filename[0]);
					break;
				}
			}

		} while (_findnext(handle, &fd) != -1);


		_findclose(handle);
	}

	Texture* ResourceManager::GetTexture(const string& tag)
	{
		Texture *texture = new Texture;
		texture->texture = textureMap[tag];
		texture->inRM = true;
		SDL_QueryTexture(texture->texture, NULL, NULL, &texture->size.width, &texture->size.height);
		texture->Init(0, 1.0, 255, 255, 255, 1.0, 1.0, 0.5, 0.5, BLENDMODE_BLEND);

		texture->id = assignGTextureId; 
		textureGarbage.insert(make_pair(assignGTextureId++,texture));
		return texture;
	}

	TTF_Font *ResourceManager::GetFont(const string& tag,int size)
	{
		return TTF_OpenFont(fontMap[tag].c_str(), size);
	}

	void ResourceManager::ClearGarbage()
	{
		for (auto i : textureGarbage)
		{
			if (i.second != nullptr) 
				delete i.second;
		}
		textureGarbage.clear();
		TextureMap().swap(textureGarbage);
	}


}