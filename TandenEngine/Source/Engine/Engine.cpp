//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include <iostream>
#include "Engine.h"
#include "Entity/Components/MeshRenderer.h"
#include "Entity/Components/Transform.h"
//Vulkan Test
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>



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



        //create test window
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::cout << extensionCount << " extensions supported" << std::endl;

        glm::mat4 matrix;
        glm::vec4 vec;
        auto test = matrix * vec;

        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }

        glfwDestroyWindow(window);

        glfwTerminate();



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
        ResourceManager::SaveProjectResources();
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
