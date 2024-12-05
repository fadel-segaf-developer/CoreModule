#include <iostream>
#include <thread>
#include "Engine.h"
#include "EntityObject.h"
#include "ChronoMaster.h"
#include "EntityManager.h"
#include "MainCharacter.h"
#include "SceneManager.h"
#include <algorithm> // For std::find, std::sort, etc.
#include <utility>  // For std::pair

namespace Engine {
    void TestEngine() {
        ChronoMaster chronoMaster;
        chronoMaster.Init(144, 1000); //limit 10 FPS and 1 second update
        SceneManager sceneManager;

        // Create entities using the factory function
        //auto entity1 = EntityObject::Create();
        //auto entity2 = MainCharacter::Create();


        while (true) {
            if (chronoMaster.IsTimeUpdate()) {
                EntityManager::UpdateAll();
                chronoMaster.DebugFrameRendered();
            }
            if (chronoMaster.IsTimeFixedUpdate()) {
                EntityManager::FixedUpdateAll();

            }
        }
    }
}


