#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include "EntityObject.h"

class EntityManager {
public:
    static void AddEntity(std::shared_ptr<EntityObject> entity);
    static void UpdateAll();
    static void FixedUpdateAll();
    static std::vector<string> GetAllEntitiesName();
    static std::vector<std::shared_ptr<EntityObject>> entities;
};

#endif // ENTITYMANAGER_H
