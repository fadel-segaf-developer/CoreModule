#ifndef CHRONOMASTER_H
#define CHRONOMASTER_H

#include <iostream>
#include <chrono>

class ChronoMaster {
public:
    ChronoMaster();

    void Init(double maxFPS = 60.0, int fixedUpdateIntervalMs = 10);
    // Initialization function for FixedUpdate
    
    // Function to check if it's time for Update
    bool IsTimeUpdate();

    // Function to check if it's time for FixedUpdate
    bool IsTimeFixedUpdate();

    // Function to update frame count and calculate FPS
    void DebugFrameRendered();

private:
    double maxFPS;
    double framesPerUpdate;
    int CurrentFPS = 0;
    int fixedUpdateIntervalMs;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastUpdate;
    std::chrono::steady_clock::time_point lastFixedUpdate;
    double frameCount;
};

#endif // CHRONOMASTER_H
