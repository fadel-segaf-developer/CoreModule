#ifndef CUSTOMSCENARIO_H
#define CUSTOMSCENARIO_H

#include <iostream>
#include <string>
#include "EntityObject.h"
#include "Scene.h"

class CustomScenario : public EntityObject, public Scene {
public:
    CustomScenario(const std::string& sceneName);

    std::string GetName() const;
    void Initialize() override;

private:
    std::string m_sceneName;
};

#endif // CUSTOMSCENARIO_H
