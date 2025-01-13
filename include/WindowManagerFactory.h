#pragma once
#ifndef WINDOW_MANAGER_FACTORY_H
#define WINDOW_MANAGER_FACTORY_H

#include "IWindowManager.h"  // Only the interface
#include "GLFWManager.h"

class WindowManagerFactory {
public:
    static std::unique_ptr<IWindowManager> CreateWindowManager(WindowManagerType type) {
        switch (type) {
        case WindowManagerType::GLFW:
            return std::make_unique<GLFWManager>();
        case WindowManagerType::SDL2:
            //return std::make_unique<SDL2WindowManager>();
            throw std::runtime_error("SDL2 window manager not implemented");
        default:
            throw std::invalid_argument("Unknown window manager type.");
        }
    }
};

#endif  // WINDOW_MANAGER_FACTORY_H
