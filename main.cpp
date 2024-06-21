#include <iostream>
#include "CoreModule.h"

int main() {
    // Initialize your CoreModule or other components here
    std::shared_ptr<CoreModule> coreModule = make_shared<CoreModule>();

    // Other initialization logic...

    // Main loop
    while (true) {
        // Update your CoreModule or other components
        coreModule->Update();

        // Other update logic...

        // Break the loop under some condition, such as game over
        
        // Only for demonstration purposes, we break after a few iterations
        static int iteration = 0;
        if (++iteration >= 5) {
            break;
        }
    }

    // Clean up resources and exit
    // coreModule.reset(); // Not necessary due to smart pointers

    return 0;
}
