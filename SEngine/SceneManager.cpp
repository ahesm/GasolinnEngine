#include"SceneManager.h"

#include"String.h"
#include"System.h"

#include<stdarg.h>

namespace gasolinn
{
	Scene*		SceneManager::previousScene = NULL;
	Scene*		SceneManager::currentScene;
	SceneMap	SceneManager::sceneMap;
	bool		SceneManager::sceneChanged = false;
	

	void SceneManager::AddScene(Scene *firstScene, ...)
	{
		va_list args;

		va_start(args, firstScene);

		std::string className = typeid(*firstScene).name();
		std::string tag = String::Split(className, " ")[1];

		sceneMap.insert(std::make_pair(tag, firstScene));
		currentScene = firstScene;
		currentScene->Initialize();

		currentScene->sceneWidth = System::width;
		currentScene->sceneHeight = System::height;
		currentScene->tag = tag;

		Scene* scene = va_arg(args, Scene*);
		printf("%s\n", tag.c_str());

		while(scene)
		{
			className = typeid(*scene).name();
			tag = String::Split(className, " ")[1];
			printf("%s\n", tag.c_str());
			sceneMap.insert(std::make_pair(tag, scene));

			scene->tag = tag;
			scene->sceneWidth = System::width;
			scene->sceneHeight = System::height;

			scene = va_arg(args, Scene*);
		}

		va_end(args);
		
	}


	Scene* SceneManager::ReplaceScene(const std::string &tag)
	{
		previousScene = currentScene;
		currentScene = sceneMap[tag];
		currentScene->Preloading();

		sceneChanged = true;

		return currentScene;
	}


	void SceneManager::Release()
	{
		currentScene->ReleaseScene();

		for (auto &scene : sceneMap)
		{
			if (scene.second != nullptr)
			{
				delete scene.second;
				scene.second = nullptr;
			}
		}
		sceneMap.clear();
		SceneMap().swap(sceneMap);
	}
}