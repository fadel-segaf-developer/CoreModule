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

## Features
- **Entity and Component System**: Create entities and attach components to them.
- **Automatic Management**: Automatic ID assignment and management of entities.
- **Scene Management**: Load, unload, and manage different scenes.
- **Event Handling**: Handle update events for entities in a structured manner.
- **Extendable**: Easily create new types of entities and behaviors.

## Getting Started
### Prerequisites
- C++17 or later
- CMake (for building the project)
- A compatible C++ compiler (e.g., GCC, Clang, MSVC)

### Building the Project
1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/coreModule.git
    cd coreModule
    ```

2. Create a build directory and navigate to it:
    ```sh
    mkdir build && cd build
    ```

3. Run CMake and build the project:
    ```sh
    cmake ..
    make
    ```

## Usage
### Creating an Entity
To create a new entity, use the `EntityObject` class:
```cpp
#include "EntityObject.h"

int main() {
    auto entity = EntityObject::Create();
    entity->AddComponent<CoreModule>();
    return 0;
}
