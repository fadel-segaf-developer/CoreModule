#include <iostream>
#include <thread>
#include "GUIManager.h"
#include "CoreModule.h"
#include "EntityObject.h"
#include "ChronoMaster.h"
#include "EntityManager.h"
#include "MainCharacter.h"
#include "SceneManager.h"
#include "WindowManagerFactory.h"
#include "Config.h"
#include <algorithm> // For std::find, std::sort, etc.
#include <utility>  // For std::pair

#include<Windows.h>



namespace CoreModule {
    int FPS = 0;
    std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();

    std::wstring GetWorkingDirectory() {
        wchar_t buffer[MAX_PATH]; // Use wchar_t for wide string
        GetCurrentDirectoryW(MAX_PATH, buffer);
        return std::wstring(buffer);
    }

    void Start()
    {
        //EXAMPLE HOW TO DEBUG ON WINDOW GUI APP
        //std::wstring workingDir = GetWorkingDirectory();
        //MessageBoxW(nullptr, workingDir.c_str(), L"Current Working Directory", MB_OK);
        //load config
        Config config;

        // Load the configuration
        if (!config.LoadConfig("config.ini")) {

           //example of window error popup
           MessageBoxW(nullptr, L"config.ini file can't be opened", L"Error", MB_ICONERROR | MB_OK);
        }

        //Time Master
        ChronoMaster chronoMaster;
        chronoMaster.Init(config.fpsLimit, 1000); 

        // Create a window manager using the factory
        std::unique_ptr<IWindowManager> windowManager = WindowManagerFactory::CreateWindowManager(WindowManagerType::GLFW);

        // Create the window
        windowManager->Init(config.windowWidth,config.windowHeight,config.windowTitle.c_str());
       // std::shared_ptr<Scene> s1 =sceneManager->addScene("Scene1");
        //s1->CreateEntity("crazy man");
       // std::shared_ptr<Scene> s2 = sceneManager->addScene("Scene2");
        //s2->CreateEntity("Ultra man");
        //std::shared_ptr<Scene> s3 = sceneManager->addScene("Scene3");
        //s3->CreateEntity("Omega man");
        
        while (!windowManager->ShouldClose()) {
            if (chronoMaster.IsTimeUpdate())
            {
                // Debug frame timing
                FPS = chronoMaster.DebugFrameRendered();

                EntityManager::UpdateAll();
                windowManager->NewFrame();
                CoreModule::RenderBackground(config.windowWidth, config.windowHeight);
                CoreModule::RenderFPSCounter(ImVec2(config.windowWidth, config.windowHeight));
                windowManager->Render();
                
            }
            if (chronoMaster.IsTimeFixedUpdate()) {
                EntityManager::FixedUpdateAll();

            }  
        }
    }
    void Exit()
    {
        //CoreModule::CleanUp();
    }

}


