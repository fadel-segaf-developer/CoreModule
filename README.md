# coreModule

Welcome to `coreModule`! This project is my attempt to replicate Unity's MonoBehaviors in C++ while deepening my understanding of the language. Through this project, I aim to create a foundation that is not only educational for myself but also beneficial for others who are learning C++ and game development concepts.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Examples](#examples)
- [License](#license)

## Introduction
`coreModule` is inspired by Unity's MonoBehaviors, which are the building blocks for scripts in Unity. The goal of this project is to replicate similar functionality in C++, providing a way to create and manage game objects and their behaviors. This project serves as both a learning exercise and a potentially useful library for others interested in game development with C++.

**New Update**: `coreModule` is now a library! 🎉 This update makes it reusable across different projects, enhancing flexibility and ease of integration. It also supports **multi-threading** for improved performance, as well as **frame rate limiting** to ensure smooth execution. The library is designed to be beautiful and efficient. ✨

While it replicates Unity's MonoBehavior system, it's written entirely in C++. **Currently**, it does not use CMake, and instead, the MSVC compiler is used for building. I may introduce CMake support in the future.

## Features
- **Entity and Component System**: Create entities and attach components to them.
- **Automatic Management**: Automatic ID assignment and management of entities.
- **Scene Management**: Load, unload, and manage different scenes.
- **Event Handling**: Handle update events for entities in a structured manner.
- **Extendable**: Easily create new types of entities and behaviors.
- **Multi-threading**: Supports multi-threading for performance optimization.
- **Frame Rate Limiting**: Limit FPS to ensure smooth performance across different hardware.
- **Beautiful Design**: Focus on code cleanliness and user-friendly interface.

## Getting Started
To get started with `coreModule`, simply include it as a dependency in your project. Currently, MSVC is the supported compiler, and you can manually integrate it without needing CMake setup.

## Usage
You can use `coreModule` in your C++ projects by including the library files and linking to the appropriate objects. Here's an example setup:

1. Download the `coreModule` source code.
2. Include the necessary header files in your project.
3. Link to the compiled `.lib` files (if applicable).

## Examples
Here are some basic examples of how to use `coreModule` in your project.

### Example 1: Testing
```cpp
#include "Engine.h"

int main() {
    Engine::TestEngine();
    
    return 0;
}
