#include "SceneManager.h"

void SceneManager::PopulateScenes() {
    // Initialize all scenes and add them to scenes map
    auto scene1 = std::make_shared<CustomScenario>("MainMenu");
    scenes[scene1->GetName()] = scene1;

    /*auto scene2 = std::make_shared<CustomScenario>("PauseMenu");
    scenes[scene2->GetName()] = scene2;*/

    // Print all scene names
    for (const auto& pair : scenes) {
        std::cout << "Scene Name: " << pair.first << std::endl;
    }
}

bool SceneManager::SceneExists(const std::string& sceneName) const {
    return scenes.find(sceneName) != scenes.end();
}


