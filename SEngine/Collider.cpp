#include "Collider.h"

#include"Object.h"
#include"Scene.h"
#include"Collision.h"

namespace gasolinn
{
	Collider * Collider::CreateABRect(Object * parent, const Ver2& ver, const Size& size)
	{
		auto collider = new Collider;

		collider->parent = parent;
		collider->type = ABRECT;
		collider->vertex = ver;
		collider->size = size;

		collider->id = parent->parent->assignColliderId++;
		parent->parent->colliderMap.insert(std::make_pair(collider->id, collider));

		return collider;
	}

	Collider * Collider::CreateOBRect(Object * parent, const Ver2& ver, const Size& size,const Vec2& dir)
	{
		auto collider = new Collider;

		collider->parent = parent;
		collider->type = OBRECT;
		collider->vertex = ver;
		collider->size = size;
		collider->dir = dir;

		collider->id = parent->parent->assignColliderId++;
		parent->parent->colliderMap.insert(std::make_pair(collider->id, collider));

		return collider;
	}

	Collider * Collider::CreateCircle(Object * parent,const Ver2& ver, int diameter)
	{
		auto collider = new Collider;

		collider->parent = parent;
		collider->type = CIRCLE;
		collider->vertex = ver;
		collider->diameter = diameter;

		collider->id = parent->parent->assignColliderId++;
		parent->parent->colliderMap.insert(std::make_pair(collider->id, collider));

		return collider;
	}

	void Collider::CollisionCheckWithAll(const std::function<void(int collider_id)>& function)
	{
		for (auto colpair : parent->parent->colliderMap)
		{
			auto collider = colpair.second;
			if (collider->type == ABRECT && CollisionToABRect(collider)) function(collider->id);
			if (collider->type == OBRECT && CollisionToOBRect(collider)) function(collider->id);
			if (collider->type == CIRCLE && CollisionToCircle(collider)) function(collider->id);
		}
	}

	bool Collider::CollisionCheckWithId(int collider_id)
	{
		auto collider = parent->parent->colliderMap[collider_id];
	
		
		if (collider->type == ABRECT) return CollisionToABRect(collider);
		if (collider->type == OBRECT) return CollisionToOBRect(collider);
		if (collider->type == CIRCLE) return CollisionToCircle(collider);
		
		return false;
	}

	void Collider::SetPosition(Ver2 ver)
	{
		vertex = ver;
	}

	void Collider::Release()
	{
		isRelease = true;
	}

	bool Collider::CollisionToABRect(Collider * other)
	{
		if (type == ABRECT)
		{
			return Collision::ABRectToRect(this->vertex.x, this->vertex.y, this->size.width, this->size.height,
				other->vertex.x, other->vertex.y, other->size.width, other->size.height);
		}
		else if (type == OBRECT)
		{
			return Collision::OBRectToRect(vertex, size, dir,
				other->vertex, other->size, Vec2(1, 0));
		}
		else if (type == CIRCLE)
		{
			return Collision::ABRectToCircle(other->vertex.x, other->vertex.y, other->size.width, other->size.height,
				vertex.x, vertex.y, diameter);
		}
		return false;
	}

	bool Collider::CollisionToOBRect(Collider * other)
	{
		if (type == ABRECT)
		{
			return Collision::OBRectToRect(vertex, size, Vec2(1, 0),
				other->vertex, other->size, other->dir);
		}
		else if (type == OBRECT)
		{
			return Collision::OBRectToRect(vertex, size, dir,
				other->vertex, other->size, other->dir);
		}
		else if (type == CIRCLE)
		{
			return Collision::OBRectToCircle(other->vertex, other->size, other->dir, vertex, diameter);
		}
		return false;
	}

	bool Collider::CollisionToCircle(Collider * other)
	{
		if (type == ABRECT)
		{
			return Collision::ABRectToCircle(vertex.x, vertex.y, size.width, size.height,
				other->vertex.x, other->vertex.y, other->diameter);
		}
		else if (type == OBRECT)
		{
			return Collision::OBRectToCircle(vertex, size, dir, other->vertex, other->diameter);
		}
		else if (type == CIRCLE)
		{
			return Collision::CircleToCircle(vertex.x, vertex.y, diameter,
				other->vertex.x, other->vertex.y, other->diameter);
		}
		return false;
	}
}