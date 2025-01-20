// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#pragma once
// Undefine 'byte' macro to prevent conflicts in rpcndr.h
#ifdef byte
#undef byte
#endif

// Standard headers
#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Windows headers
#include <windows.h>

// Third-party libraries
#include <SDL.h>

// Other project-wide headers
#include <filesystem> // C++17 filesystem (if used)


#endif //PCH_H
