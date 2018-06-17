#include"Scene.h"

#include"System.h"
#include"Camera.h"

#include<algorithm>

namespace gasolinn
{
	void Scene::Pause()
	{
		isPause = true;
	}

	void Scene::Resume()
	{
		isPause = false;
	}

	void Scene::Reset()
	{
		ReleaseScene();
		Initialize();
	}

	void Scene::SortObjectsWithZ()
	{
		sort(objectVector.begin(), objectVector.end(), [](const Object* ob1, const Object* ob2) {
			return ob1->z < ob2->z;
		});
	}


	int Scene::AddObjectWithTag(Object* object, Ver2 pos, Vec2 vec, const std::string &tag)
	{
		object->parent = this;
		object->id = assignObjectId++;
		object->pos = pos;
		object->vector = vec;
		object->tag = tag;
		object->Initialize();

		objectMap.insert(std::make_pair(object->id, object));
		objectVector.push_back(object);

		SortObjectsWithZ();

		return object->id;
	}

	int Scene::AddObjectWithTag(Object* object, double x, double y, double direction, double speed, const std::string &tag)
	{
		return AddObjectWithTag(object, Ver2(x, y), Vector::getVecWithDirAndSize(direction, speed), tag);
	}

	int Scene::AddObjectWithTag(Object* object, Ver2 ver, const std::string &tag)
	{
		return AddObjectWithTag(object, ver, Vec2(), tag);
	}

	int Scene::AddObjectWithTag(Object* object, double x, double y, const std::string &tag)
	{
		return AddObjectWithTag(object, x, y, 0, 0, tag);
	}

	int Scene::AddObjectWithTag(Object* object, const std::string &tag)
	{
		return AddObjectWithTag(object, 0, 0, tag);
	}


	int Scene::AddObject(Object *object, Ver2 ver, Vec2 vec)
	{
		return AddObjectWithTag(object, ver, vec, "-970521");
	}

	int Scene::AddObject(Object* object, double x, double y, double direction, double speed)
	{
		return AddObjectWithTag(object, x, y, direction, speed, "-970521");
	}

	int Scene::AddObject(Object *object, Ver2 ver)
	{
		return AddObject(object, ver, Vec2());
	}

	int Scene::AddObject(Object* object, double x, double y)
	{
		return AddObject(object, x, y, 0, 0);
	}

	int Scene::AddObject(Object* object)
	{
		return AddObject(object, System::width/2,System::height/2);
	}

	//void Scene::CreateTimeline(Timeline *timeline)
	//{
	//	timeline->parent = this;
	//	timelines.insert(std::make_pair(assignTimelineId++, timeline));
	//}

	void Scene::Background()
	{
		Camera::Update();
		SDL_GetMouseState(&mouse.x, &mouse.y);


		//TimelineMap::iterator timEnd = timelines.end();
		//for (timIter = timelines.begin(); timIter != timEnd;)
		//{
		//	(*timIter).second->Background();
		//}

		for (auto iter = objectVector.begin(); iter != objectVector.end();)
		{
			(*iter)->Background();
			if ((*iter)->isRelease) {
				objectMap.erase((*iter)->id);
				if (*iter != nullptr)
				{
					delete (*iter);
					(*iter) = nullptr;
				}
				iter = objectVector.erase(iter);
			}
			else ++iter;
		}

	}

	void Scene::ReleaseScene()
	{	
		Release();

		for (auto iter = objectVector.begin(); iter != objectVector.end();)
		{
			auto obj = *iter;
			(*iter)->Release();
			iter = objectVector.erase(iter);
			if (obj != nullptr)
			{
				delete obj;
				obj = nullptr;
			}
		}

		objectVector.clear();
		objectMap.clear();

		ObjectVector().swap(objectVector);
		ObjectMap().swap(objectMap);

		ResourceManager::ClearGarbage();

		//ColliderMap::iterator colliderIterator;
		//ColliderMap::iterator colliderEnd = colliderMap.end();
		//for (colliderIterator = colliderMap.begin(); colliderIterator != colliderEnd;)
		//{
		//	colliderMap.erase(colliderIterator++);
		//}

		//ClickableMap::iterator clickableIterator;
		//ClickableMap::iterator clickableEnd = clickableMap.end();
		//for (clickableIterator = clickableMap.begin(); clickableIterator != clickableEnd;)
		//{
		//	clickableMap.erase(clickableIterator++);
		//}
	}

}