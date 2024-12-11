# CoreModule

Welcome to **CoreModule**! This project is an independent implementation inspired by game development frameworks like Unity. Built entirely in C++, it provides a lightweight, reusable foundation for creating and managing entities and their behaviors. While designed as a learning exercise, **CoreModule** also offers practical utility for developers exploring C++ and game development concepts.

## Table of Contents
- [Introduction](#introduction)
- [What's New?](#whats-new)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Examples](#examples)
- [License](#license)

## Introduction

**CoreModule** is a C++ library that implements an entity-component-based behavior system, offering a foundation for building game-like functionality. Inspired by systems like Unity's MonoBehaviour, it introduces concepts like entities, components, and event-driven updates while remaining lightweight and independent of any specific engine.

This library is not a clone of Unity's MonoBehaviour but rather an independent solution that shares similar ideas while introducing its own improvements and flexibility. With features like multi-threading and frame rate limiting, **CoreLogic** is optimized for performance while maintaining ease of use.

**Note:** **CoreModule** is designed for learning and general-purpose use. It is built from scratch without any proprietary code from Unity Technologies.

## What's New?

- **Renamed `CoreModule` class to `CoreLogic`**: More descriptive class name. `CoreModule` is now a namespace.
- **Added `CoreModule` namespace**: Encapsulated the entire logic under a namespace for better organization.
- **Added DearImGUI framework**: Integrated as a separate library for scalable GUI development.

## Features

- **Entity-Component System**: Create and manage entities, attach components, and define behaviors.
- **Event-Driven Updates**: Structured handling of lifecycle events like `Update`.
- **Scene Management**: Load, unload, and transition between scenes seamlessly.
- **Performance Optimization**:
  - Multi-threaded support for parallel processing.
  - Frame rate limiting for consistent performance.
- **Extendable Architecture**: Easily add custom components and systems to fit your project needs.
- **Open-Source and Lightweight**: Designed to integrate with any project, without engine-specific dependencies.
- **GUI Support**: Integrated DearImGUI for scalable and customizable GUI development.

## Getting Started

To start using **CoreModule**, follow these steps:

1. Clone the repository from GitHub.
2. Include the **CoreModule** source files in your project.
3. Use an MSVC compiler to build the library.
4. Integrate **CoreModule** into your project by including the necessary headers.
5. **Future Plans**: 
- Integrating frame limitation and rendering from ImGUi
- A clickable button to create new entity
- An example of entity object of 2D that can be rendered
- An example of frame limitation with stress test
- An example of multithreading entities and its performance debugging details

## Usage

Here’s an example setup to get started with **CoreModule**:

### Include the Engine Header:
```cpp
#include "CoreModule.h"

CoreModule::Initialize(800,600);
CoreModule::MainLoop();
CoreModule::Exit();
```
Don't forget to include your own window management library on the game, or just copy the example of my code and use SDL like this :

```cpp
#include "CoreModule.h"

#include "backends/imgui_impl_sdl2.h"
#include <SDL.h>
int SDL_main(int argc, char* argv[]) {

    CoreModule::InitializeImGui(800, 600);
    CoreModule::MainLoop();
    CoreModule::Exit();

    return 0;
}

```
