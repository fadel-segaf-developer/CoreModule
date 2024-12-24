#define STB_IMAGE_IMPLEMENTATION
#include "GUIManager.h"
#include "CoreModule.h"
#include "stb_image.h"

namespace CoreModule {


	SDL_Window* window;
	SDL_GLContext gl_context;

	void CoreModule:: InitializeWindow(int width, int height, const char* windowName)
	{
		// Create window and OpenGL context here
		window = SDL_CreateWindow(windowName,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height, SDL_WINDOW_OPENGL);
		if (!window) {
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
		}

		gl_context = SDL_GL_CreateContext(window);
		if (!gl_context) {
			std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(window);
			SDL_Quit();
		}

		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init("#version 130");
	}
	


	void CoreModule::CustomWindow()
	{
		// ImGui UI rendering
		ImGui::Begin("Custom Window");
		ImGui::Text("This is a Custom Window.");
		ImGui::End();
	}

	void CoreModule::Render()
	{

		
		// Set the OpenGL context and clear the screen
		SDL_GL_MakeCurrent(window, gl_context);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Get the display size from ImGui
		ImVec2 displaySize = ImGui::GetIO().DisplaySize;


		// getting the style
		ImGuiStyle& style = ImGui::GetStyle();
		//BACKGROUND

		// Resize ImGui window to match the SDL window size
		int windowWidth, windowHeight;
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);
		ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0)); // Position it at the top-left corner (optional)

		style.WindowBorderSize = 0.0f; // Remove window borders
		style.FrameBorderSize = 0.0f;  // Remove frame borders (for buttons, inputs, etc.)
		style.ScrollbarSize = 0.0f;    // Optionally remove scrollbar sizes if not needed
		style.WindowPadding = ImVec2(0.0f, 0.0f); // Remove padding for windows, making them compact
		ImGui::SetNextWindowBgAlpha(0.0f);          

		ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoResize);
		RenderImageBackground();

		ImGui::End();

		//FPS VIEW
		// Calculate position for top-right corner
		float xPos = displaySize.x - 100; // Adjust based on the text width
		float yPos = 10;                  // Margin from the top

		// Render FPS counter directly on the main viewport
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos)); // Position in the top-right corner
		ImGui::SetNextWindowBgAlpha(0.0f);          // Make the background transparent
		ImGui::Begin("FPSOverlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoResize);

		// Add FPS text
		ImGui::Text("FPS: %d", CoreModule::FPS); // Replace 144 with dynamic FPS calculation
		//End the FPS view
		ImGui::End();


		//SCENE VIEW
		// Calculate position for top-right corner
		xPos = 10; // Adjust based on the text width
		yPos = 10;                  // Margin from the top

		ImGui::SetNextWindowPos(ImVec2(xPos, yPos)); // Position in the top-right corner
		ImGui::SetNextWindowBgAlpha(0.0f);          // Make the background transparent
		ImGui::Begin("SceneOverlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_AlwaysAutoResize);

		// Add Scene text
		ImGui::Text("Scene Counter : %d", CoreModule::sceneManager->Scenes.size());
		for (auto& scene : CoreModule::sceneManager->Scenes)
		{
			std::string sceneName = scene.first;
			ImGui::Text("[Scene] - %s", sceneName.c_str());

			for (auto& entity : scene.second->m_mEntities)
			{
				std::string EntityName = entity.first;
				ImGui::Text("  > [Enitity] - %s", EntityName.c_str());

			}
		}

		


		//End the Scene View
		ImGui::End();

		// Finalize ImGui frame
		ImGui::Render();

		// Render ImGui draw data to OpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the window buffer to display the rendered frame
		SDL_GL_SwapWindow(window);
	}


	// Function to load image using stb_image
	GLuint CoreModule::LoadTextureFromFile(const char* filename)
	{
		int width, height, channels;
		unsigned char* image_data = stbi_load(filename, &width, &height, &channels, 0);
		if (!image_data)
		{
			//std::cerr << "Failed to load image: " << filename << std::endl;
			return 0;
		}

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// Set texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Upload image data to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

		stbi_image_free(image_data);  // Don't forget to free the image data

		return texture;
	}

	// Render image using ImGui
	void CoreModule::RenderImage()
	{
		GLuint textureID = LoadTextureFromFile("C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/image2.png");

		if (textureID)
		{
			// Pass textureID directly as ImTextureID, no need for casting
			ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(200, 200));
		}
	}


	void CoreModule::RenderImageBackground()
	{
		int windowWidth, windowHeight;
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		GLuint textureID = LoadTextureFromFile("C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/image.png");

		if (textureID)
		{
			ImVec2 windowPos = ImGui::GetWindowPos();

			// Stretch the image to fill the SDL window (the actual app window size)
			ImGui::GetWindowDrawList()->AddImage(
				(ImTextureID)(intptr_t)textureID,           // Texture ID
				windowPos,                            // Image position (top-left corner of the window)
				ImVec2(windowPos.x + windowWidth, windowPos.y + windowHeight), // Bottom-right corner (stretched to the actual window size)
				ImVec2(0, 0),                         // Top-left texcoord
				ImVec2(1, 1),                         // Bottom-right texcoord
				IM_COL32(255, 255, 255, 255)          // White color for no tint
			);
		}
	}



	void CoreModule::CleanUp()
	{
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

}

