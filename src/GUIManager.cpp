#define STB_IMAGE_IMPLEMENTATION
#include "GUIManager.h"
#include "CoreModule.h"
#include "stb_image.h"
#include "Config.h"

namespace CoreModule {


	SDL_Window* window;
	SDL_GLContext gl_context;
	int windowWidth, windowHeight;
	GLuint BackgroundTextureID = LoadTexture("C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/bg.png");


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

		windowWidth = width;
		windowHeight = height;
		// Initialize ImGui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 130");

		

		//initialize data

		const char* fontPath = "C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/Font/TT Octosquares Trial Condensed ExtraLight.ttf";

		// Load the font and add it to the font atlas
		io.Fonts->AddFontFromFileTTF(fontPath, 25.0f);  // 16.0f is the font size

		
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
		// --- Set the OpenGL context and clear the screen ---
		SDL_GL_MakeCurrent(window, gl_context);
		glClear(GL_COLOR_BUFFER_BIT);

		// --- Start the ImGui frame ---
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// Get the display size and prepare styles
		ImVec2 displaySize = ImGui::GetIO().DisplaySize;
		ImGuiStyle& style = ImGui::GetStyle();
		ConfigureImGuiStyle(style);

		// --- Render Background ---
		//RenderBackground();

		// --- Render FPS Counter ---
		RenderFPSCounter(displaySize);

		// --- Render Scenes and Entities ---
		RenderScenesAndEntities(displaySize, style);

		ImGui::ShowDemoWindow();

		// --- Finalize ImGui frame ---
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// --- Swap the buffer to display the rendered frame ---
		SDL_GL_SwapWindow(window);
	}

	// Configure ImGui style settings
	void CoreModule::ConfigureImGuiStyle(ImGuiStyle& style)
	{
		style.WindowBorderSize = 0.0f; // Remove window borders
		style.FrameBorderSize = 0.0f;  // Remove frame borders
		style.ScrollbarSize = 0.0f;    // Disable scrollbars
		style.WindowPadding = ImVec2(0.0f, 0.0f); // Remove window padding
	}

	// Render the background as a fullscreen image
	void CoreModule::RenderBackground(float windowWidth, float windowHeight)
	{
		ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowBgAlpha(0.0f); // Fully transparent background

		ImGui::Begin("Background", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);

		BackgroundTextureID = LoadTexture("C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/bg.png");

		// Bind and render the background texture
		glBindTexture(GL_TEXTURE_2D, BackgroundTextureID);
		RenderImageBackground(BackgroundTextureID, ImVec2(windowWidth,windowHeight));

		ImGui::End();
	}

	// Render the FPS counter in the top-right corner
	void CoreModule::RenderFPSCounter(const ImVec2& displaySize)
	{
		float xPos = displaySize.x - 100; // Position from the right edge
		float yPos = 10;                  // Position from the top edge

		ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
		ImGui::SetNextWindowBgAlpha(0.0f); // Transparent background

		ImGui::Begin("FPSOverlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

		// Display the FPS count
		ImGui::Text("FPS: %d", CoreModule::FPS);

		ImGui::End();
	}

	// Render all scenes and their respective entities
	void CoreModule::RenderScenesAndEntities(const ImVec2& displaySize, ImGuiStyle& style)
	{
		float xPos = 10;    // Initial x-position
		float yPos = 10;    // Initial y-position
		int rowCounter = 0; // Tracks rows for scene positioning
		int lastEntityCount = 0;
		int columnCounter = 0;
		float lastYPos = yPos;

		// Padding configurations
		float scenePadding = 150.0f;
		float entityPadding = 100.0f;

		for (auto& scene : CoreModule::sceneManager->Scenes)
		{
			// Prepare scene-specific settings
			std::string sceneName = scene.first;
			std::shared_ptr<Scene> currentScene = scene.second;
			int entityCount = currentScene->m_mEntities.size();
			float prevEntityYPadding = (lastEntityCount * entityPadding);

			// Calculate position for the current scene
			float totalYPadding = (rowCounter == 0 ? lastYPos : lastYPos + prevEntityYPadding + scenePadding);

			// Handle new columns when exceeding the window height
			if ((totalYPadding + entityCount * entityPadding) >= static_cast<float>(windowHeight))
			{
				columnCounter++;
				rowCounter = 0;
				lastYPos = yPos;
				totalYPadding = yPos;
			}
			else
			{
				lastYPos = totalYPadding;
			}

			float sceneXPos = xPos + (columnCounter * 350);
			RenderScene(sceneName, currentScene, sceneXPos, totalYPadding, entityPadding);

			// Update counters
			rowCounter++;
			lastEntityCount = entityCount;
		}
	}

	// Render a single scene and its entities
	void CoreModule::RenderScene(const std::string& sceneName, const std::shared_ptr<Scene>& scene, float xPos, float yPos, float entityPadding)
	{
		// Parent window configuration
		ImGui::SetNextWindowSize(ImVec2(300.0f, 400.0f)); // Fixed size for the parent window
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
		ImGui::SetNextWindowBgAlpha(0.1f); // Semi-transparent background

		ImGui::Begin(sceneName.c_str(), nullptr, ImGuiWindowFlags_NoCollapse);

		// Display scene details
		ImGui::Text("Scene Name: %s", sceneName.c_str());
		ImGui::Text("Entity Count: %d", (int)scene->m_mEntities.size());

		// Entity creation input
		ImGui::PushItemWidth(150.0f);
		if (ImGui::InputText(" ", scene->entityTextBuffer, sizeof(scene->entityTextBuffer), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			std::string entityName(scene->entityTextBuffer);
		}
		ImGui::SameLine();
		if (ImGui::Button("Add Entity"))
		{
			if (strlen(scene->entityTextBuffer) > 0)
			{
				scene->CreateEntity(scene->entityTextBuffer);
				memset(scene->entityTextBuffer, 0, sizeof(scene->entityTextBuffer));
			}
		}

		// Add spacing before the child window
		ImGui::Spacing();

		// Render entities in a scrollable child window
		ImVec2 childSize(ImGui::GetContentRegionAvail().x, 0); // Fixed height for scrollbar
		ImGui::BeginChild("Entities", childSize, true, ImGuiWindowFlags_None);

		for (auto& entity : scene->m_mEntities)
		{
			ImGui::Text("Entity Name: %s", entity.first.c_str());
			ImGui::Spacing(); // Adds spacing between entities
		}

		ImGui::EndChild();
		ImGui::End();
	}





	// Render a single entity
	void CoreModule::RenderEntity(const std::string& entityName, float xPos, float yPos)
	{
		//ImGui::SetNextWindowSize(ImVec2(250.0f, 0.0f)); // Fixed width, auto-resize height
		//ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
		//ImGui::SetNextWindowBgAlpha(0.2f); // Semi-transparent background

		//ImGui::Begin(entityName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs);

		
	}

	GLuint LoadTexture(const char* filename)
	{
		int width, height, channels;
		unsigned char* image_data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
		if (!image_data)
		{
			std::cerr << "Failed to load image: " << filename << std::endl;
			return 0;
		}
		
		

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

		stbi_image_free(image_data);

		return texture;
	}

	void CoreModule::RenderImageBackground(GLuint i_textureID, ImVec2 size)
	{
		if (i_textureID)
		{
			ImVec2 windowPos = ImGui::GetWindowPos();

			// Stretch the image to fill the SDL window (the actual app window size)
			ImGui::GetWindowDrawList()->AddImage(
				(ImTextureID)(intptr_t)i_textureID,           // Texture ID
				windowPos,                            // Image position (top-left corner of the window)
				ImVec2(windowPos.x + size.x, windowPos.y + size.y), // Bottom-right corner (stretched to the actual window size)
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
		ImGui::DestroyContext();
		SDL_GL_DeleteContext(gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

}

