//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include <iostream>
#include "Engine.h"
#include "Entity/Components/ComponentHeader.h"


namespace TandenEngine {

    Game * Engine::mGame;

    void Engine::StartEngine() {
        std::cout<< "Please specify Project File directory: ";
        std::cin >> mProjectDirectory;

        mProjectSettings = Serializer::LoadProject(mProjectDirectory);

        RenderingSystem::InitSystem();
        ResourceManager::ImportAssetsFolder();
        RenderingSystem::InitGraphicsPipeline();

        if(mProjectSettings != nullptr)
            mProjectSettings->PrintProjectInfo(); //Display the info to make sure it's correct
        else
            std::cout<<"Error Loading Project Start Engine\n";

        if(mGame == nullptr)
        {
            std::cout<<"Error No Game Object\n";
            return;
        }
        mGame->StartUpGame();

        std::cout<<"Start Main\n";
    }

    void Engine::RunEngine() {
        while (!exitStatus) {
            //std::cout << "Running Loop \n";
            //Get input
            Input::GetInput();

            //Process Events
            EventSystem::ProcessEvents();

            //Update all registered physics objects
            PhysicsSystem::PhysicsUpdate();

            //Update all the loaded scenes
            for (const auto &scene : mLoadedScenes) {
                if (scene != nullptr)
                    scene->Update();
            }

            //Update game specific systems
            mGame->UpdateGame();

            //Render all registered renderer components
            RenderingSystem::Draw();

            //Wait for frame time
            Timer::WaitForFrameTime();
        }
    }

    void Engine::StopEngine() {
        std::cout << "Closing Engine\n";
        mGame->ShutDownGame();
        //RenderingSystem::Cleanup();
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

    void Engine::ProcessEventKeyboard(KeyboardEvent *theEvent) { //Only process special events needed for the engine
        std::cout << "Got event\n";
        switch (theEvent->mVal) {
            case 27: //Escape key to exit
                exitStatus = 1;
                break;
        }
    }

}
