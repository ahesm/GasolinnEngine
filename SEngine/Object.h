#pragma once

#include<string>
#include<unordered_map>
#include"Structs.h"
#include"Vector.h"
#include"ResourceManager.h"
#include"Texture.h"

using namespace std;
using namespace gfunc;


namespace gasolinn
{
	class Scene;
	class Object
	{
	public:
		Object() {};
	public:
		Vec2	vector;
		Ver2	pos;

		int		id;
		int		z = 0;

		bool	isRelease = false;

		string	tag = "-970521";

		Scene*	parent;


	public:
		void Background();
		void ReleaseObject();

	public:
		void DrawTexturePart(Texture *texture, float x, float y, int left, int top, int width, int height, int r, int g, int b);
		void DrawTexturePart(Texture *texture, float x, float y, int left, int top, int width, int height);
		void DrawTexturePart(Texture *texture, Ver2 pos, Rect rect);
		
		void DrawTexture(Texture *texture, float x, float y);
		void DrawTexture(Texture *texture, Ver2 pos);
		void DrawTexture(Texture *texture);

		int DrawNumber(Texture *texture, int number, int space, float x, float y, int align);

	public:
		//Collider *GetCollider(int id);

	public:
		virtual void Initialize() = 0;
		virtual void Step() = 0;
		virtual void Draw() = 0;
		virtual void Release() = 0;
	};

	typedef unordered_map<int, Object*> ObjectMap;
	typedef vector<Object*> ObjectVector;
}