#define STB_IMAGE_IMPLEMENTATION
#include "GUIManager.h"
#include "CoreModule.h"
#include "stb_image.h"

namespace CoreModule {


	SDL_Window* window;
	SDL_GLContext gl_context;
	int windowWidth, windowHeight;
	GLuint BackgroundTextureID;


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
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
		ImGui_ImplOpenGL3_Init("#version 130");

		InitializeData();
	}

	void CoreModule::InitializeData()
	{
		ImGuiIO& io = ImGui::GetIO();
		const char* fontPath = "C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/Font/TT Octosquares Trial Condensed ExtraLight.ttf";

		// Load the font and add it to the font atlas
		io.Fonts->AddFontFromFileTTF(fontPath, 25.0f);  // 16.0f is the font size

		BackgroundTextureID = LoadTexture("C:/Users/FRYS-017/OneDrive/Documents/INDIVIDUAL PROJECTS/C++/CoreModule/bg.png");
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
		// Get the ImGui IO structure
		
		//BACKGROUND

		// Resize ImGui window to match the SDL window size
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
		

		glBindTexture(GL_TEXTURE_2D, BackgroundTextureID);
		RenderImageBackground(BackgroundTextureID);
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
			ImGuiWindowFlags_AlwaysAutoResize);

		// Add FPS text
		ImGui::Text("FPS: %d", CoreModule::FPS); 
		//End the FPS view
		ImGui::End();


		//SCENE DEBUG VIEW
		// Calculate position for top-right corner
		xPos = 10; // Adjust based on the text width
		yPos = 10;                  // Margin from the top

		ImGui::SetNextWindowPos(ImVec2(xPos, yPos)); // Position in the top-right corner
		ImGui::SetNextWindowBgAlpha(0.0f);          // Make the background transparent
		ImGui::Begin("SceneOverlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_AlwaysAutoResize);

		// scene debug
		ImGui::Text("Scene Counter : %d", CoreModule::sceneManager->Scenes.size());
		int i = 0;
		for (auto& scene : CoreModule::sceneManager->Scenes)
		{
			std::string sceneName = scene.first;
			ImGui::Text("[Scene [%d]] - %s",i, sceneName.c_str());

			for (auto& entity : scene.second->m_mEntities)
			{
				std::string EntityName = entity.first;
				ImGui::Text("  > [Enitity] - %s", EntityName.c_str());

			}
			i = i + 1;
		}
		//End the Scene debug View
		ImGui::End();

		//New Scene input field
		xPos = 10; // Adjust based on the text width
		yPos = displaySize.y - 100;// Margin from the top
		ImGui::SetNextWindowPos(ImVec2(xPos, yPos)); // Position in the top-right corner
		ImGui::SetNextWindowBgAlpha(0.0f);          // Make the background transparent
		ImGui::Begin("Text Input Window", nullptr, ImGuiWindowFlags_NoDecoration |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_AlwaysAutoResize);
		// Declare sceneTextBuffer as a persistent buffer, initialized with an empty string
		static char sceneTextBuffer[128] = "";

		// Render the input text field
		if (ImGui::InputText("Enter the scene name", sceneTextBuffer, sizeof(sceneTextBuffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
			// Ensure null-termination of the buffer
			sceneTextBuffer[sizeof(sceneTextBuffer) - 1] = '\0';

			// Safely convert the buffer to std::string
			std::string sceneName(sceneTextBuffer);

			// Check if the name is valid (not empty)
			if (!sceneName.empty()) {
				// Add a new scene
				std::shared_ptr<Scene> s1 = sceneManager->addScene(sceneName);
				//s1->CreateEntity("crazy man");
			}
			else {
				// Handle the case of empty input
				std::cerr << "Scene name is empty!" << std::endl;
			}
		}

		// Input field
		ImGui::End();



		// Finalize ImGui frame
		ImGui::Render();

		// Render ImGui draw data to OpenGL
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the window buffer to display the rendered frame
		SDL_GL_SwapWindow(window);
	}


	GLuint CoreModule::LoadTextureFromFile(const char* filename)
	{
		// Load the image using stb_image
		int width, height, channels;
		unsigned char* image_data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);  // Force RGBA format
		if (!image_data)
		{
			std::cerr << "Failed to load image: " << filename << std::endl;
			return 0;
		}

		// Check for the bit depth and handle it
		if (channels != 4)
		{
			//std::cerr << "Unsupported image format. Expected RGBA (32-bit) but got " << channels << " channels." << std::endl;
			stbi_image_free(image_data);
			return 0;
		}

		// Resize image if it's bigger than the window size
		if (width > windowWidth || height > windowHeight)
		{
			float scale_factor = std::min(static_cast<float>(windowHeight) / width, static_cast<float>(windowHeight) / height);
			width = static_cast<int>(width * scale_factor);
			height = static_cast<int>(height * scale_factor);
		}

		// Create a new image with resized dimensions
		unsigned char* resized_image_data = new unsigned char[width * height * 4];  // Use RGBA (4 channels)

		// Bilinear interpolation resizing
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				// Get the coordinates in the original image
				float src_x = (x + 0.5f) * width / float(windowWidth) - 0.5f;
				float src_y = (y + 0.5f) * height / float(windowHeight) - 0.5f;

				// Clamp the source coordinates to ensure they are within bounds
				int x0 = std::max(0, std::min(width - 1, int(src_x)));
				int y0 = std::max(0, std::min(height - 1, int(src_y)));
				int x1 = std::max(0, std::min(width - 1, x0 + 1));
				int y1 = std::max(0, std::min(height - 1, y0 + 1));

				// Calculate the bilinear interpolation weights
				float dx = src_x - x0;
				float dy = src_y - y0;
				float weight_x = 1.0f - dx;
				float weight_y = 1.0f - dy;

				for (int c = 0; c < 4; ++c)  // Use 4 channels (RGBA)
				{
					// Interpolate between the four surrounding pixels
					unsigned char pixel = (unsigned char)(
						weight_x * weight_y * image_data[(y0 * width + x0) * 4 + c] +
						dx * weight_y * image_data[(y1 * width + x0) * 4 + c] +
						weight_x * dy * image_data[(y0 * width + x1) * 4 + c] +
						dx * dy * image_data[(y1 * width + x1) * 4 + c]
						);
					resized_image_data[(y * width + x) * 4 + c] = pixel;
				}
			}
		}

		// Generate OpenGL texture and upload the resized image data
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Upload the resized image data to OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, resized_image_data);

		// Free the original image data and resized image data
		stbi_image_free(image_data);
		delete[] resized_image_data;

		return texture;
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

	void CoreModule::AddAlphaChannel(unsigned char*& image_data, int& width, int& height, int& channels)
	{
		if (channels == 4)
		{
			// Already has an alpha channel; no modification needed
			return;
		}

		// Create a new buffer for RGBA data
		unsigned char* rgba_data = new unsigned char[width * height * 4]; // 4 channels (R, G, B, A)

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				int src_index = (y * width + x) * channels;
				int dst_index = (y * width + x) * 4;

				// Copy RGB channels
				rgba_data[dst_index + 0] = image_data[src_index + 0]; // Red
				rgba_data[dst_index + 1] = (channels > 1) ? image_data[src_index + 1] : image_data[src_index + 0]; // Green
				rgba_data[dst_index + 2] = (channels > 2) ? image_data[src_index + 2] : image_data[src_index + 0]; // Blue

				// Add opaque alpha channel
				rgba_data[dst_index + 3] = 255; // Alpha
			}
		}

		// Free the original image data and replace it with the new RGBA data
		stbi_image_free(image_data);
		image_data = rgba_data;
		channels = 4; // Update channels to 4
	}



	// Render image using ImGui
	void CoreModule::RenderImage(std::string i_imageAddress)
	{
		GLuint textureID = LoadTextureFromFile(i_imageAddress.c_str());

		if (textureID)
		{
			// Pass textureID directly as ImTextureID, no need for casting
			ImGui::Image((ImTextureID)(intptr_t)textureID, ImVec2(200, 200));
		}
	}


	void CoreModule::RenderImageBackground(GLuint i_textureID)
	{
		if (i_textureID)
		{
			ImVec2 windowPos = ImGui::GetWindowPos();

			// Stretch the image to fill the SDL window (the actual app window size)
			ImGui::GetWindowDrawList()->AddImage(
				(ImTextureID)(intptr_t)i_textureID,           // Texture ID
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

