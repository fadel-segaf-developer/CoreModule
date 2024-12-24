#include "SceneManager.h"
#include <memory>

std::shared_ptr<Scene> SceneManager::addScene(std::string i_sceneName)
{
	for (const auto& pair : Scenes) {
		if (pair.first == i_sceneName)
		{
			return nullptr;
		}
	}

	std::shared_ptr<SceneManager> self = shared_from_this();
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(self);
	Scenes[i_sceneName] = scene;
	return scene;
}
