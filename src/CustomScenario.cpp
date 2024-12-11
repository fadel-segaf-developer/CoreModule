#include "CustomScenario.h"
#include "MainCharacter.h"
#include <iostream>
#include <thread>
#include <vector>
#include <functional> 
#include <random>
#include <algorithm>
#include <mutex>

const int totalTasks = 0;
std::mutex mtx; // Mutex for synchronization

CustomScenario::CustomScenario(SceneManager* i_pSceneManager) : 
    Scene(m_sceneName, i_pSceneManager), m_sceneName("CustomScenario"), m_pSceneManager(i_pSceneManager){
    //std::cout << "CustomScenario with Scene '" << m_sceneName << "' created\n";
    Initialize();
}

std::string CustomScenario::GetName() const {
    return m_sceneName;
}

void CustomScenario::threadTask(int threadId, int start, int end) {
    try {
        for (int i = start; i <= end; ++i) {
            // std::cout << i << std::endl;
            std::lock_guard<std::mutex> lock(mtx); // Acquire lock
            //Mutexes are a fundamental synchronization mechanism in multithreaded programming, and they are not inherently "bad" for performance.
            auto MC = MainCharacter::Create("obj" + std::to_string(i));
            
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception in thread " << threadId << ": " << e.what() << std::endl;
    }
}

void CustomScenario::UseThread()
{
    // Get the number of hardware threads available
    unsigned int numThreads = std::thread::hardware_concurrency();
    if (numThreads == 0) {
        numThreads = 1; // Fallback to 1 if the number of hardware threads is not computable
    }

    std::vector<std::thread> threads;
    int tasksPerThread = (totalTasks + numThreads - 1) / numThreads; // Calculate tasks per thread


    std::cout << numThreads;
    // Create threads
    if (m_pSceneManager != nullptr || this != nullptr) {
        for (unsigned int i = 0; i < numThreads; ++i) {
            int start = i * tasksPerThread + 1;
            int end = std::min((i + 1) * static_cast<unsigned int>(tasksPerThread), static_cast<unsigned int>(totalTasks));
            try {
                threads.emplace_back(&CustomScenario::threadTask, this, i, start, end);
            }
            catch (exception e) {

            }
        }
    }
    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }
}


void CustomScenario::Initialize() {
    std::cout << "CustomScenario Init\n";
    
    for (int i = 1; i < 5; i++)
    {
        auto AutoEntity = EntityObject::Create("Obj", m_pSceneManager, this);
    }
    
    //UseThread();
}


