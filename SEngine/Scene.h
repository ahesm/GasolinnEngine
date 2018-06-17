#pragma once

#include"Object.h"
#include"Collider.h"

#include<unordered_map>
#include<string>

namespace gasolinn
{
	class Scene
	{
	public:
		Scene() {};
	public:
		bool				 isPause = false;
		int					 assignObjectId = 0;
		int					 assignColliderId = 0;
		int					 assignClickableId = 0;
		int					 assignTimelineId = 0;
		
		std::string			 tag;
		SDL_Point			 mouse;

		int					 x = 0, y = 0;
		int					 sceneWidth, sceneHeight;

		ObjectMap			 objectMap;
		ObjectVector		 objectVector;

		ColliderMap          colliderMap;
		//ClickableMap        clickableMap;

		//TimelineMap timelines;
		//TimelineMap::iterator timIter;
	public:
		virtual void Initialize() = 0;
		virtual void Release() = 0;
		virtual void Preloading() {};
		virtual bool Loading(Scene *prevScene) { return false; };

	public:

		void Pause();
		void Resume();

		void Reset();

		int AddObjectWithTag(Object* object, Ver2 ver, Vec2 vec, const std::string &tag);
		int AddObjectWithTag(Object* object, double x, double y, double direction, double speed, const std::string &tag);
		int AddObjectWithTag(Object* object, Ver2 ver, const std::string &tag);
		int AddObjectWithTag(Object* object, double x, double y, const std::string &tag);
		int AddObjectWithTag(Object* object, const std::string &tag);

		int AddObject(Object* object, Ver2 ver, Vec2 vec);
		int AddObject(Object* object, double x, double y, double direction, double speed);
		int AddObject(Object* object, Ver2 ver);
		int AddObject(Object* object, double x, double y);
		int AddObject(Object* object);

		//void CreateTimeline(Timeline *timeline);
	public:
		void SortObjectsWithZ();
	public:
		void Background();
		void ReleaseScene();
	};
	typedef unordered_map<std::string, Scene*> SceneMap;
}