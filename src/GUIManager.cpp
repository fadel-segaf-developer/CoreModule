#include "GUIManager.h"
#include "CoreModule.h"
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

		// Calculate position for top-right corner
		float xPos = displaySize.x - 100; // Adjust based on the text width
		float yPos = 10;                  // Margin from the top

		// Render FPS counter directly on the main viewport
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos)); // Position in the top-right corner
		ImGui::SetNextWindowBgAlpha(0.0f);          // Make the background transparent
		ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoResize);

		// Add FPS text
		ImGui::Text("FPS: %d", CoreModule::FPS); // Replace 144 with dynamic FPS calculation

		ImGui::End();

		// Finalize ImGui frame
		ImGui::Render();

		// Render ImGui draw data to OpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the window buffer to display the rendered frame
		SDL_GL_SwapWindow(window);
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

