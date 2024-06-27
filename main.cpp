#include <iostream>
#include "EntityObject.h"

int main() {
    // Set the fixed update time interval for all CoreModule instances
    CoreModule::SetFixedUpdateTime(0.05f);

    // Create an entity which automatically initializes with CoreModule
    std::vector<std::shared_ptr<EntityObject>> entities;

    // Create 10 entities
    for (int i = 0; i < 10; ++i) {
        auto entity = std::make_shared<EntityObject>();
        entities.push_back(entity);

        // Optionally add components to each entity
        auto coreModule = entity->AddComponent<CoreModule>();
        // Add other components as needed...
    }
        
    //Create 1 unique entity
    // 
    // Main loop (for demonstration)
    while (true) {
        for (size_t i = 0; i < entities.size(); ++i) 
        {
            entities[i]->Update();
            entities[i]->FixedUpdate();
        }
        // Break the loop under some condition, such as entity over

        // Only for demonstration purposes, break after a few iterations
        static int iteration = 0;
        if (++iteration >= 10000) {
            break;
        }
    }

    // No need to explicitly call Destroy(); shared_ptr will handle cleanup

    return 0;
}
