#include "ChronoMaster.h"

ChronoMaster::ChronoMaster()
    : maxFPS(60.0), framesPerUpdate(0.0), fixedUpdateIntervalMs(10),
    startTime(std::chrono::steady_clock::now()), lastUpdate(startTime), lastFixedUpdate(startTime), frameCount(0.0) {
}

void ChronoMaster::Init(double maxFPS, int fixedUpdateIntervalMs) {
    this->fixedUpdateIntervalMs = fixedUpdateIntervalMs;
    this->maxFPS = std::max(maxFPS, 10.0); // Ensure maxFPS is at least 60.0
    framesPerUpdate = 1.0 / this->maxFPS; // Time per Update cycle
}

bool ChronoMaster::IsTimeUpdate() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>(currentTime - lastUpdate).count();

    if (elapsedSeconds >= framesPerUpdate) {
        lastUpdate = currentTime;
        return true;
    }

    return false;
}

bool ChronoMaster::IsTimeFixedUpdate() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastFixedUpdate).count();

    if (elapsedMilliseconds >= fixedUpdateIntervalMs) {
        lastFixedUpdate = currentTime;
        return true;
    }

    return false;
}

void ChronoMaster::DebugFrameRendered() {
    // Increment frame count
    ++frameCount;

    // Calculate elapsed time since start
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedSeconds = std::chrono::duration<double>(currentTime - startTime).count();

    // Calculate current FPS every second
    if (elapsedSeconds >= 1.0) {
        
        double currentFPS = frameCount / elapsedSeconds;
        if (static_cast<int>(currentFPS) != CurrentFPS)
        {
            system("cls");
            std::cout << "FPS: " << static_cast<int>(currentFPS) << std::endl;
        }
        CurrentFPS = static_cast<int>(currentFPS);
        // Reset for the next second
        frameCount = 0.0;
        startTime = currentTime;
    }
}
