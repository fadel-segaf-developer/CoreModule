// IRenderingManager.h
#pragma once

class IRenderingManager {
public:
    virtual ~IRenderingManager() {}

    virtual void Init() = 0; // Initialize the rendering system
    virtual void Render() = 0; // Render a frame
    virtual void CleanUp() = 0; // Clean up resources
};
