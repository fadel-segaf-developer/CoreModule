#include "EntityObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CustomScenario.h"

SceneManager::SceneManager() 
{

    addScene(new CustomScenario(this));
}

void SceneManager::SwitchScene(int& i_sceneNumber)
{
    auto mapScene = scenes.begin();
    std::advance(mapScene, i_sceneNumber);
    Scene* loadedScene = mapScene->second;
}

bool SceneManager::SceneExists(const std::string& sceneName) const 
{
    return scenes.find(sceneName) != scenes.end();
}

bool SceneManager::addScene(Scene* i_Scene)
{
    if (i_Scene == NULL)
        return false;

    if (scenes.find(i_Scene->GetName()) != scenes.end())
        return false;

    scenes[i_Scene->GetName()] = i_Scene;

    return true;
}

bool SceneManager::storeEntityData(Scene* i_scene, shared_ptr<EntityObject> i_entityObject)
{
    if (i_scene != nullptr || i_entityObject != nullptr)
    {
        entityData[i_scene] = i_entityObject;
        return true;
    }
    else 
    {
        return false;
    }
}


