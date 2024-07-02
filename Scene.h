#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "EntityObject.h"
#include "SceneManager.h"



class Scene : public EntityObject {
public:
    Scene(const std::string& i_Name, SceneManager* i_pSceneManager);
    ~Scene();

    void AddEntity(std::shared_ptr<EntityObject> entity);
    void RemoveEntity(std::shared_ptr<EntityObject> entity);
    void ClearEntities();
    const std::string& GetName() const { return m_sSceneName; }
    const std::vector<std::shared_ptr<EntityObject>>& GetEntities() const { return entities; }

private:
    std::string m_sSceneName;
    SceneManager* m_pSceneManager = nullptr;
    std::vector<std::shared_ptr<EntityObject>> entities;
};

#endif // SCENE_H
