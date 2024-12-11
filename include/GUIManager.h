#pragma once
#include "CoreModule.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>

namespace CoreModule {
	
	static constexpr bool USING_SDL2 = true;
	static constexpr bool USING_OPENGL3 = true;

	class GUIManager
	{
	public:
		GUIManager() {};
	};
}