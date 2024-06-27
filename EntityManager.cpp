#include "EntityManager.h"

std::vector<std::shared_ptr<EntityObject>> EntityManager::entities;

void EntityManager::AddEntity(std::shared_ptr<EntityObject> entity) {
    entities.push_back(entity);
}

void EntityManager::UpdateAll() {
    for (auto& entity : entities) {
        entity->Update();
    }
}

void EntityManager::FixedUpdateAll() {
    for (auto& entity : entities) {
        entity->FixedUpdate();
    }
}
