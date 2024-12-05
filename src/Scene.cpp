#include "Scene.h"

Scene::Scene(const std::string& name, SceneManager* i_pSceneManager)
    :m_sSceneName(name)
{

}

Scene::~Scene() {
    entities.clear();
}

void Scene::AddEntity(std::shared_ptr<EntityObject> entity) {
    entities.push_back(entity);
}

void Scene::RemoveEntity(std::shared_ptr<EntityObject> entity) {
    // Remove entity from the vector
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);
    }
}


void Scene::ClearEntities() {
    entities.clear();
}
