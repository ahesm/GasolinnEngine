#pragma once

#include<functional>
#include"Structs.h"
#include"Vector.h"

#include<unordered_map>


//대폭 수정 필요

namespace gasolinn
{
	using namespace gfunc;
	class Object;

	enum BoundingType {
		CIRCLE, ABRECT, OBRECT
	};

	class Collider
	{
	public:
		Object *parent;

		Ver2 vertex;
		Vec2 dir;
		Size size;
		int diameter;

		int id;

		bool enable = true;
		bool isRelease = false;

		BoundingType type;

	public:
		static Collider *CreateABRect(Object *parent, const Ver2& ver, const Size& size);
		static Collider *CreateOBRect(Object *parent, const Ver2& ver, const Size& size, const Vec2& dir);
		static Collider *CreateCircle(Object *parent, const Ver2& ver, int diameter);



		/*매개변수 id는 충돌한 상대 collider의 id*/
		void CollisionCheckWithAll(const std::function<void(int collider_id)> &function);
		bool CollisionCheckWithId(int collider_id);

		void SetPosition(Ver2 ver);

		void Release();

	public:
		bool CollisionToABRect(Collider *other);
		bool CollisionToOBRect(Collider *other);
		bool CollisionToCircle(Collider *other);

	};

	typedef std::unordered_map<int,Collider*> ColliderMap;
}