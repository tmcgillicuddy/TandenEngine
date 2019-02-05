#include <iostream>
#include "Engine.h"
#include "Entity/Components/ComponentHeader.h"
#include "../Core/Debugger/Debug.h"

namespace TandenEngine {

    Game * Engine::mGame;

    void Engine::StartEngine() {
        std::cout<< "Please specify Project File directory: ";
        std::cin >> mProjectDirectory;

        mProjectSettings = Serializer::LoadProject(mProjectDirectory);

        RenderingSystem::InitSystem();
        ResourceManager::ImportAssetsFolder();
        RenderingSystem::InitGraphicsPipeline();

        if (mProjectSettings != nullptr) {
            // Display the info to make sure it's correct
            mProjectSettings->PrintProjectInfo();
        } else {
            std::cout << "Error Loading Project Start Engine\n";
        }

        if (mGame == nullptr) {
            std::cout << "Error No Game Instance\n";
            // return;
        } else {
            mGame->StartUpGame();
        }

        std::cout << "Start Main\n";
    }

    void Engine::RunEngine() {
        while (!exitStatus) {
            // Get input
            Input::GetInput();

            if (Input::GetKeyDown(KeyCode::ESC)) {
                exitStatus = 1;
                continue;
            }
            // Process Events
            EventSystem::ProcessEvents();

            // Update all registered physics objects
            PhysicsSystem::PhysicsUpdate();

            // Update all the loaded scenes
            for (const auto &scene : mLoadedScenes) {
                if (scene != nullptr)
                    scene->Update();
            }

            // Update game specific systems
            if (mGame != nullptr)
                mGame->UpdateGame();

            // Render all registered renderer components
            RenderingSystem::Draw();

            // Wait for frame time
            Timer::WaitForFrameTime();
        }
    }

    void Engine::StopEngine() {
        std::cout << "Closing Engine\n";
        if (mGame != nullptr)
            mGame->ShutDownGame();
        // RenderingSystem::Cleanup();
    }

    Engine::Engine() {
        EventSystem::RegisterListener(this);
    }

    void Engine::ProcessEvent(Event *theEvent) {
        switch (theEvent->mType) {
            case Event::INPUT:
                ProcessEventKeyboard(static_cast<KeyboardEvent *>(theEvent));
                break;
        }
    }

    // Only process special events needed for the engine
    void Engine::ProcessEventKeyboard(KeyboardEvent *theEvent) {
        std::cout << "Got event\n";
        switch (theEvent->mVal) {
            case 27:  // Escape key to exit
                exitStatus = 1;
                break;
        }
    }

}  // namespace TandenEngine
