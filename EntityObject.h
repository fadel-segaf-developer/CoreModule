#ifndef ENTITYOBJECT_H
#define ENTITYOBJECT_H

#include <iostream>
#include <vector>
#include <memory>
#include "CoreModule.h"

class EntityObject : public std::enable_shared_from_this<EntityObject> {
public:
    EntityObject(); // Constructor
    void Initialize(); // Initialization function

    // Add a component to this entity
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    // Lifecycle methods
    void Update();
    void FixedUpdate();
    void Destroy();

private:
    std::vector<std::shared_ptr<CoreModule>> components; // List of components
};

template<typename T, typename... Args>
std::shared_ptr<T> EntityObject::AddComponent(Args&&... args) {
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    component->SetEntityObject(shared_from_this());
    components.push_back(component);
    return component;
}

#endif // ENTITYOBJECT_H
