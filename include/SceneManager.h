#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include <map>

class Scene;

class SceneManager 
{
public:
    SceneManager();
    bool SceneExists(const std::string& sceneName) const;
    void SwitchScene(int& i_sceneNumber);
    bool storeEntityData(Scene* i_scene, shared_ptr<EntityObject> i_entityObject);

private:
    bool addScene(Scene* i_Scene);
    std::map<std::string, Scene*> scenes;
    std::map<Scene*, shared_ptr<EntityObject>> entityData;

    bool Debug = true;
};

#endif // SCENEMANAGER_H
