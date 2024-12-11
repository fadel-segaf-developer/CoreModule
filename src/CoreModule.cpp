#include <iostream>
#include <thread>
#include "GUIManager.h"
#include "CoreModule.h"
#include "EntityObject.h"
#include "ChronoMaster.h"
#include "EntityManager.h"
#include "MainCharacter.h"
#include <algorithm> // For std::find, std::sort, etc.
#include <utility>  // For std::pair



namespace CoreModule {
    //SDL variables
    int FPS = 0;
    std::shared_ptr<SceneManager> sceneManager = nullptr;
    void Start()
    {
        ChronoMaster chronoMaster;
        chronoMaster.Init(60, 1000); 
        sceneManager = std::make_shared<SceneManager>();

        bool engineRunning = true;
        while (engineRunning) {
            if (chronoMaster.IsTimeUpdate()) {
                EntityManager::UpdateAll();
                if (CoreModule::USING_SDL2 && CoreModule::USING_OPENGL3)
                {
                    SDL_Event event;
                    while (SDL_PollEvent(&event)) {
                        if (event.type == SDL_QUIT) engineRunning = false;
                        ImGui_ImplSDL2_ProcessEvent(&event);
                    }
                    // Debug frame timing
                    FPS = chronoMaster.DebugFrameRendered();

                    // Render the UI and the scene
                    CoreModule::Render();

                }
            }
            if (chronoMaster.IsTimeFixedUpdate()) {
                EntityManager::FixedUpdateAll();

            }
            
        }
    }

    void Exit()
    {
        CoreModule::CleanUp();
    }


    
}


