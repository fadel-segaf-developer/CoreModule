#include "CustomScenario.h"
#include "MainCharacter.h"

CustomScenario::CustomScenario(const std::string& sceneName) : EntityObject(), Scene(sceneName), m_sceneName(sceneName) {
    std::cout << "CustomScenario with Scene '" << sceneName << "' created\n";
    Initialize();
}

std::string CustomScenario::GetName() const {
    return m_sceneName;
}

void CustomScenario::Initialize() {
    std::cout << "CustomScenario Init\n";
    // Additional initialization logic

    auto AutoEntity1 = EntityObject::Create("Player");
    auto CustomEntity1 = MainCharacter::Create("tes");
    this->AddEntity(CustomEntity1);
}
