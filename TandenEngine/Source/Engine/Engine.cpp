//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include <iostream>
#include "Engine.h"
#include "Entity/Components/ComponentHeader.h"


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
        auto *testGO = newScene->CreateGameObject(); //TODO remove these tests'
        auto *testGO1 = newScene->CreateGameObject(); //TODO remove these tests
        auto *testGO2 = newScene->CreateGameObject(); //TODO remove these tests

        testGO->AddComponent<MeshRenderer>(); //TODO remove these tests
        //testGO->AddComponent<SphereCollider>(); //TODO remove these tests
        //std::cout << "Made Sphere" << std::endl;
        testGO->AddComponent<SphereCollider>(); //TODO remove these tests
        testGO->GetComponent<SphereCollider>()->mTransform->position = Vector3(-1.0, 0.0, 0.0);
        testGO->SetName("Sphere 1");
        testGO1->AddComponent<SphereCollider>(); //TODO remove these tests
        testGO1->GetComponent<SphereCollider>()->mTransform->position = Vector3(1.0, 0.0, 0.0);
        testGO->SetName("Sphere 2");
        testGO2->AddComponent<BoxCollider>(); //TODO remove these tests
        testGO2->GetComponent<BoxCollider>()->mTransform->position = Vector3(0.5, 0.0, 0.0);
        testGO->SetName("Box 1");
        mLoadedScenes.emplace_back(newScene); //TODO remove these tests

        auto *testPrefab = new Prefab();
        testPrefab->CreatePrefab(testGO);
        testPrefab->SavePrefab();

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

            //Render all registered renderer components
            RenderingSystem::Draw();

            //Wait for frame time
            Timer::WaitForFrameTime();
        }
    }

    void Engine::StopEngine() {
        std::cout << "Closing Engine\n";

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
