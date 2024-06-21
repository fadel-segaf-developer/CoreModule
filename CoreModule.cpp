#include "CoreModule.h"
#include "GameObject.h" // Assuming GameObject class exists

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

void CoreModule::Initialize() {
    if (gameObject.lock()) {
        Awake(); // Call Awake if attached to a GameObject
        Start(); // Call Start if attached to a GameObject
    }
}

void CoreModule::AttachToGameObject(shared_ptr<GameObject> gameObject) {
    this->gameObject = gameObject;
    AutoCallLifecycleFunctions();
}

std::shared_ptr<GameObject> CoreModule::GetGameObject() const {
    return gameObject.lock();
}

void CoreModule::AutoCallLifecycleFunctions() {
    // Call Awake only once
    if (!started) {
        started = true;
        Initialize(); // Call the initialization function during attachment
    }
}
