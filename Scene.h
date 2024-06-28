#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>
#include <memory>
#include "EntityObject.h"

class Scene {
public:
    Scene(const std::string& name);
    ~Scene();

    void AddEntity(std::shared_ptr<EntityObject> entity);
    void RemoveEntity(std::shared_ptr<EntityObject> entity);
    void ClearEntities();

    const std::string& GetName() const { return name; }
    const std::vector<std::shared_ptr<EntityObject>>& GetEntities() const { return entities; }

private:
    std::string name;
    std::vector<std::shared_ptr<EntityObject>> entities;
};

#endif // SCENE_H
