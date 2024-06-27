#include <iostream>
#include <vector>
#include "EntityObject.h"
#include "ChronoMaster.h"

int main() {
    ChronoMaster chronoMaster;
    chronoMaster.Init(10.0,30); // Initialize ChronoMaster with maximum FPS (e.g., 240.0)

    std::vector<std::shared_ptr<EntityObject>> entities;

    // Example: Create an entity which automatically initializes with CoreModule
    auto uniqueEntity = std::make_shared<EntityObject>();
    entities.push_back(uniqueEntity);
    auto coreModule = uniqueEntity->AddComponent<CoreModule>();

    while (true) {
        // Check if it's time for FixedUpdate
        if (chronoMaster.IsTimeFixedUpdate()) {
            // Example: coreModule->FixedUpdate();
        }

        // Check if it's time for Update
        if (chronoMaster.IsTimeUpdate()) {
            uniqueEntity->Update();
            chronoMaster.DebugFrameRendered();
        }

        
    }

    return 0;
}
