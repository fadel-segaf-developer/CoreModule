#include "CoreLogic.h"
#include "EntityObject.h"

int frame = 0;

CoreLogic::CoreLogic() : started(false) {}

void CoreLogic::Awake() {
    std::cout << "CoreLogic Awake\n";
}

void CoreLogic::Start() {
    std::cout << "CoreLogic Start\n";
}

void CoreLogic::Update() {
    std::cout << "CoreLogic Update\n";
}
void CoreLogic::FixedUpdate() {
    //std::cout << "CoreLogic FixedUpdate\n";
}

void CoreLogic::OnDestroy() {
    std::cout << "CoreLogic OnDestroy\n";
}

void CoreLogic::SetEntityObject(std::shared_ptr<EntityObject> entity) {
    this->entityObject = entity;
}


