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
	GLuint LoadTexture(const char* filename);
	void RenderImageBackground(GLuint i_textureID);
	void ConfigureImGuiStyle(ImGuiStyle& style);
	void RenderBackground();
	void RenderScenesAndEntities(const ImVec2& displaySize, ImGuiStyle& style);
	void RenderFPSCounter(const ImVec2& displaySize);
	void RenderScene(const std::string& sceneName, const std::shared_ptr<Scene>& scene, float xPos, float yPos, float entityPadding);
	void RenderEntity(const std::string& entityName, float xPos, float yPos);

	class GUIManager
	{
	public:
		GUIManager() {};

		
	};
}