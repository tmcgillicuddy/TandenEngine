//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include <iostream>
#include "Engine.h"
#include "Entity/Components/MeshRenderer.h"
#include "Entity/Components/Transform.h"
//Vulkan Test
#define GLFW_INCLUDE_VULKAN
#include "../../Libraries/GLFW/include/GLFW/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "../../Libraries/GLM/glm/vec4.hpp"
#include "../../Libraries/GLM/glm/mat4x4.hpp"



namespace TandenEngine {

    void Engine::StartEngine() {
        std::cout<< "Please specify Project File directory: ";
        std::cin >> mProjectDirectory;

        mProjectSettings = Serializer::LoadProject(mProjectDirectory);
        ResourceManager::ImportAssetsFolder();

        if(mProjectSettings != nullptr)
            mProjectSettings->PrintProjectInfo(); //Display the info to make sure it's correct
        else
            std::cout<<"Error Loading Project Start Engine\n";


        RenderingSystem::InitSystem();

        //ADD TEST DATA TODO REMOVE THESE
        auto *newScene = new Scene(); //TODO remove these tests
        auto *testGO = newScene->CreateGameObject(); //TODO remove these tests
        testGO->AddComponent<MeshRenderer>(); //TODO remove these tests
        mLoadedScenes.emplace_back(newScene); //TODO remove these tests
        std::cout<<"Start Main\n";

        ResourceManager::AddResource(newScene);


        system("pause");

    }

    void Engine::RunEngine() {

        while (!exitStatus) {
            std::cout << "Running Loop \n";
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

            //Render all registered renderer components
            RenderingSystem::Draw();

            //Wait for frame time
            Timer::WaitForFrameTime();
        }
    }

    void Engine::StopEngine() {
        std::cout << "Closing Engine\n";

        RenderingSystem::Cleanup();

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
