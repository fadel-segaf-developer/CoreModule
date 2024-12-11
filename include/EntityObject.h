#ifndef ENTITYOBJECT_H
#define ENTITYOBJECT_H

#include <iostream>
#include <vector>
#include <memory>
#include "CoreLogic.h"
#include "SceneManager.h"

class Scene;

class EntityObject : public std::enable_shared_from_this<EntityObject> {
public:
    static std::shared_ptr<EntityObject> Create(const std::string& i_entityName, SceneManager* i_pSceneManger, Scene* i_Scene);

    // Lifecycle methods
    virtual void Initialize(); // Initialization function
    virtual void Update();
    virtual void FixedUpdate();
    virtual void Destroy();

    // Add a component to this entity
    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    string GetEntityName();
    void SetEntityName(string i_sName);


protected:
    EntityObject() = default; // Constructor is protected to allow access by derived classes

private:
    std::vector<std::shared_ptr<CoreLogic>> components; // List of components
    static bool isNameUnique(string i_name);
    string entityName;
};

template<typename T, typename... Args>
std::shared_ptr<T> EntityObject::AddComponent(Args&&... args) {
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    component->SetEntityObject(shared_from_this());
    components.push_back(component);
    return component;
}

#endif // ENTITYOBJECT_H
