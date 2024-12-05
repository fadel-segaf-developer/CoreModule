# CoreModule

Welcome to `CoreModule`! This project is an independent implementation inspired by game development frameworks like Unity. Built entirely in C++, it provides a lightweight, reusable foundation for creating and managing entities and their behaviors. While designed as a learning exercise, `CoreModule` also offers practical utility for developers exploring C++ and game development concepts.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Examples](#examples)
- [License](#license)

## Introduction

`CoreModule` is a C++ library that implements an **entity-component-based behavior system**, offering a foundation for building game-like functionality. Inspired by systems like Unity's MonoBehaviour, it introduces concepts like entities, components, and event-driven updates while remaining lightweight and independent of any specific engine.

This library is not a clone of Unity's MonoBehaviour but rather an independent solution that shares similar ideas while introducing its own improvements and flexibility. With features like multi-threading and frame rate limiting, `CoreModule` is optimized for performance while maintaining ease of use.

> **Note**: `CoreModule` is designed for learning and general-purpose use. It is built from scratch without any proprietary code from Unity Technologies.

### What's New?
- **Modular Library Design**: Fully reusable across projects.
- **Multi-threading Support**: Improved performance with parallel processing.
- **Frame Rate Limiting**: Ensures smooth performance across various hardware setups.
- **Clean and Efficient API**: A focus on beautiful and extensible code design.

---

## Features

- **Entity-Component System**: Create and manage entities, attach components, and define behaviors.
- **Event-Driven Updates**: Structured handling of lifecycle events like `Update`.
- **Scene Management**: Load, unload, and transition between scenes seamlessly.
- **Performance Optimization**:
  - Multi-threaded support for parallel processing.
  - Frame rate limiting for consistent performance.
- **Extendable Architecture**: Easily add custom components and systems to fit your project needs.
- **Open-Source and Lightweight**: Designed to integrate with any project, without engine-specific dependencies.

---

## Getting Started

To start using `CoreModule`, follow these steps:

1. Clone the repository from [GitHub](https://github.com/your-repo-link).
2. Include the `CoreModule` source files in your project.
3. Use an **MSVC compiler** to build the library.
4. Integrate `CoreModule` into your project by including the necessary headers.

> **Future Plans**: Support for CMake integration is planned for easier cross-platform builds.

---

## Usage

Here’s an example setup to get started with `CoreModule`:

1. **Include the Engine Header**:
   Include the library header files in your project.
2. **Initialize and Use the Engine**:
   Use the provided APIs to create entities and define behaviors.

### Example 1: Testing the Core Module
```cpp
#include "Engine.h"

int main() {
    // Initialize the test engine
    Engine::TestEngine();
    
    return 0;
}
