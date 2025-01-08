#pragma once
#include <memory>
#include <map>
#include "EntityObject.h"
class SceneManager;
class Scene : public std::enable_shared_from_this<Scene>
{
public:
	Scene(std::shared_ptr<SceneManager> i_pSceneManager);

	void CreateEntity(std::string i_entityName);
	std::map<std::string, std::shared_ptr<EntityObject>> m_mEntities;

	char entityTextBuffer[128] = "";

private:
	std::shared_ptr<SceneManager> m_pSceneManager;
	
};

