#include <iostream>
#include <thread>
#include "EntityObject.h"
#include "ChronoMaster.h"
#include "EntityManager.h"
#include "MainCharacter.h"
#include "SceneManager.h"

int main() {
    ChronoMaster chronoMaster;
    chronoMaster.Init(10,1000); //limit 10 FPS and 1 second update

    SceneManager sceneManager;
    sceneManager.PopulateScenes();

    // Create entities using the factory function
    //auto entity1 = EntityObject::Create();
    //auto entity2 = MainCharacter::Create();

    while (true) {
        if (chronoMaster.IsTimeUpdate()) {
            EntityManager::UpdateAll();
            //chronoMaster.DebugFrameRendered();
        }
        if (chronoMaster.IsTimeFixedUpdate()) {
            EntityManager::FixedUpdateAll();
            
        }
    }
}


