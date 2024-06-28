#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <unordered_map>
#include <memory>
#include <string>
#include "CustomScenario.h"

class SceneManager {
public:
    void PopulateScenes();
    bool SceneExists(const std::string& sceneName) const;

private:
    std::unordered_map<std::string, std::shared_ptr<CustomScenario>> scenes;
};

#endif // SCENEMANAGER_H
