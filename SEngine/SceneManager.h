#pragma once

#include<string>
#include"Scene.h"

namespace gasolinn
{
	class SceneManager
	{
	public:
		static Scene*		previousScene;
		static Scene*		currentScene;
		static SceneMap		sceneMap;

		static bool			sceneChanged;

	public:
		static void AddScene(Scene *firstScene, ...);

		static Scene* ReplaceScene(const std::string &tag);

		static void Release();
	};
}
/*
Scene A,B�� �ְ� A���� B�� �Ѿ��
A B-preloading B-loading A-release B-init B
*/