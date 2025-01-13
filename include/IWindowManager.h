// IWindowManager.h
#pragma once

#include <memory>
#include <stdexcept> 

enum class WindowManagerType {
    GLFW,
    SDL2
    // Add more window managers here
};

class IWindowManager {
public:
    virtual ~IWindowManager() {}

    virtual bool Init(int width, int height, const char* windowTitle) = 0;
    virtual void NewFrame() = 0;
    virtual void Render() = 0;
    virtual void PollEvents() = 0;
    virtual void SwapBuffers() = 0;
    virtual bool ShouldClose() = 0;
};
