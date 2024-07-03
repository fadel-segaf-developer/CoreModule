#include "EntityObject.h"
#include "EntityManager.h"

string Uniquifier(string i_name)
{
    string unqName = i_name;
    int counter = 0;
    for (const auto& existingName : EntityManager::GetAllEntitiesName()) {
        while (existingName == unqName) {
            unqName = i_name +"_"+ to_string(counter);
            counter += 1;
        }
    }
    return unqName;
    
}



std::shared_ptr<EntityObject> EntityObject::Create(const std::string& i_entityName, SceneManager* i_pSceneManger, Scene* i_Scene) {

    string nameEnt;
    
    
    nameEnt = Uniquifier(i_entityName);

    auto entity = std::shared_ptr<EntityObject>(new EntityObject());
    entity->SetEntityName(nameEnt);
    i_pSceneManger->storeEntityData(i_Scene, entity);
    entity->Initialize();

    EntityManager::AddEntity(entity);
    entity->AddComponent<CoreModule>(); // Automatically add CoreModule after registering with EntityManager
    return entity;

    return nullptr;
}



void EntityObject::Initialize() {
   //std::cout << "EntityObject " << entityName << " initialized\n";
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

void EntityObject::SetEntityName(string i_sName) {
    entityName = i_sName;
}

string EntityObject::GetEntityName() {
    return entityName;
}

bool EntityObject::isNameUnique(string i_name) {
    for (const auto& existingName : EntityManager::GetAllEntitiesName()) {
        if (existingName == i_name) {
            std::cout << "Entity with name '" << i_name << "' already exists. Creation aborted." << std::endl;
            return false; // Return nullptr or empty shared_ptr to indicate failure
        }
    }
    return true;
}
