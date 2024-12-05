#include "MainCharacter.h"
#include "EntityManager.h"


std::shared_ptr<MainCharacter> MainCharacter::Create(const std::string& name) {
    auto entity = std::shared_ptr<MainCharacter>(new MainCharacter());
    entity->SetEntityName(name);
    entity->nameObj = entity->GetEntityName();
    entity->x = stoi(entity->nameObj.substr(3, entity->nameObj.size()));
    entity->Initialize();
    EntityManager::AddEntity(entity);
    entity->AddComponent<CoreModule>(); // Automatically add CoreModule after registering with EntityManager
    return entity;
}
void MainCharacter::CustomFunction() {
    std::cout << "MainCharacter custom function\n";
}

void MainCharacter::Initialize() {
    //std::cout <<"Created " << this->nameObj << endl;
}

void MainCharacter::Update() {

    //std::cout << this->nameObj << " calc : " << x;
    
    if (x > 50000)
    {
        x = x / 2;
    }
    else {
        x = x + x;
    }
    //std::cout << " into " << x << endl;
    
}

