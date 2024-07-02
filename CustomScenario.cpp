#include "CustomScenario.h"
#include "MainCharacter.h"

CustomScenario::CustomScenario(SceneManager* i_pSceneManager) : 
    Scene(m_sceneName, i_pSceneManager), m_sceneName("CustomScenario"){
    std::cout << "CustomScenario with Scene '" << m_sceneName << "' created\n";
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
