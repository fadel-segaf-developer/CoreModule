#ifndef CUSTOMSCENARIO_H
#define CUSTOMSCENARIO_H

#include <iostream>
#include <string>
#include "EntityObject.h"
#include "Scene.h"



class CustomScenario : 
    public Scene {
public:
    CustomScenario(SceneManager* m_pSceneManager);

    std::string GetName() const;
    void Initialize() override;

private:
    void UseThread();
    std::string m_sceneName;
    void threadTask(int threadId, int start, int end);
    SceneManager* m_pSceneManager = nullptr;
};

#endif // CUSTOMSCENARIO_H
