#include "MainCharacter.h"
#include "EntityManager.h"

std::shared_ptr<MainCharacter> MainCharacter::Create(const std::string& name) {
    auto entity = std::shared_ptr<MainCharacter>(new MainCharacter());
    entity->Initialize();
    EntityManager::AddEntity(entity);
    entity->AddComponent<CoreModule>(); // Automatically add CoreModule after registering with EntityManager
    return entity;
}


void MainCharacter::CustomFunction() {
    std::cout << "MainCharacter custom function\n";
}

void MainCharacter::Update() {
    std::cout << "Oy I'm talkin ere >:(\n";
}
