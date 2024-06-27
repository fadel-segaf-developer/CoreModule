#include "EntityObject.h"

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
