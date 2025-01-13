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
#include <algorithm> // For std::find, std::sort, etc.
#include <utility>  // For std::pair

#include<Windows.h>



namespace CoreModule {
    int FPS = 0;
    std::shared_ptr<SceneManager> sceneManager = std::make_shared<SceneManager>();
    void Start()
    {
        ChronoMaster chronoMaster;
        chronoMaster.Init(144, 1000); 

        // Create a window manager using the factory
        std::unique_ptr<IWindowManager> windowManager = WindowManagerFactory::CreateWindowManager(WindowManagerType::GLFW);

        // Create the window
        windowManager->Init(1280,720,"Gim");

       // std::shared_ptr<Scene> s1 =sceneManager->addScene("Scene1");
        //s1->CreateEntity("crazy man");
       // std::shared_ptr<Scene> s2 = sceneManager->addScene("Scene2");
        //s2->CreateEntity("Ultra man");
        //std::shared_ptr<Scene> s3 = sceneManager->addScene("Scene3");
        //s3->CreateEntity("Omega man");
        
        while (!windowManager->ShouldClose()) {
            if (chronoMaster.IsTimeUpdate())
            {
                EntityManager::UpdateAll();
                windowManager->NewFrame();
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


