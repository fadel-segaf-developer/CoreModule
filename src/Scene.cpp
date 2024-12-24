#include "Scene.h"

Scene::Scene(std::shared_ptr<SceneManager> i_pSceneManager)
	:m_pSceneManager(i_pSceneManager)
{

}

void Scene::CreateEntity(std::string i_entityName)
{
	std::shared_ptr<Scene> self = shared_from_this();
	m_mEntities[i_entityName] = EntityObject::Create(i_entityName, m_pSceneManager, self);
}
