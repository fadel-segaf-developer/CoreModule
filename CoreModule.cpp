#include "CoreModule.h"
#include "EntityObject.h"

int frame = 0;

CoreModule::CoreModule() : started(false) {}

void CoreModule::Awake() {
    std::cout << "CoreModule Awake\n";
}

void CoreModule::Start() {
    std::cout << "CoreModule Start\n";
}

void CoreModule::Update() {
    std::cout << "CoreModule Update\n";
}
void CoreModule::FixedUpdate() {
    std::cout << "CoreModule FixedUpdate\n";
}

void CoreModule::OnDestroy() {
    std::cout << "CoreModule OnDestroy\n";
}

void CoreModule::SetEntityObject(std::shared_ptr<EntityObject> entity) {
    this->entityObject = entity;
}


