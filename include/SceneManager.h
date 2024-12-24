#pragma once
#include "Scene.h"

#include <string>
#include <vector>
#include <map>
class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager() {};
	std::shared_ptr<Scene> addScene(std::string i_sceneName);

	std::map<std::string, std::shared_ptr<Scene>> Scenes;
};

