#include "CustomScenario.h"

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

    auto CustomEntity1 = EntityObject::Create();
    this->AddEntity(CustomEntity1);
}
