#include "EntityObject.h"
#include "EntityManager.h"

std::shared_ptr<EntityObject> EntityObject::Create() {
    auto entity = std::shared_ptr<EntityObject>(new EntityObject());
    entity->Initialize();
    EntityManager::AddEntity(entity);
    entity->AddComponent<CoreModule>(); // Automatically add CoreModule after registering with EntityManager
    return entity;
}

EntityObject::EntityObject() {
    std::cout << "EntityObject constructor\n";
    Initialize();
}

void EntityObject::Initialize() {
    std::cout << "EntityObject initialized\n";
}

void EntityObject::Update() {
    for (auto& component : components) {
        component->Update();
    }
}

void EntityObject::FixedUpdate() {
    for (auto& component : components) {
        component->FixedUpdate();
    }
}

void EntityObject::Destroy() {
    for (auto& component : components) {
        component->OnDestroy();
    }
    components.clear();
}
