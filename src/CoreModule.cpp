#include <iostream>
#include <thread>
#include "GUIManager.h"
#include "CoreModule.h"
#include "EntityObject.h"
#include "ChronoMaster.h"
#include "EntityManager.h"
#include "MainCharacter.h"
#include "SceneManager.h"
#include <algorithm> // For std::find, std::sort, etc.
#include <utility>  // For std::pair

#include<Windows.h>



namespace CoreModule {
    int FPS = 0;
    std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();
    void Start()
    {
        bool engineRunning = true;
        ChronoMaster chronoMaster;
        chronoMaster.Init(144, 1000); 

        std::shared_ptr<Scene> s1 =sceneManager->addScene("Scene1");
        s1->CreateEntity("crazy man");
        std::shared_ptr<Scene> s2 = sceneManager->addScene("Scene2");
        s2->CreateEntity("Ultra man");
        std::shared_ptr<Scene> s3 = sceneManager->addScene("Scene3");
        s3->CreateEntity("Omega man");
        
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


