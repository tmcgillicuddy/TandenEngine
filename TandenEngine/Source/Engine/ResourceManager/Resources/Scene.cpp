//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Scene.h"

namespace TandenEngine {

    GameObject *Scene::CreateGameObject() {
        auto newGO = mGameObjects.emplace_back(std::make_unique<GameObject>()).get();
        return newGO;
    }

    bool Scene::DestroyGameObject() {
        return false;
    }

    GameObject *Scene::FindGameObject() {
        return nullptr;
    }

    void Scene::Update() {
        std::cout << "Updating Scene \n";
        for (const auto &gO : mGameObjects) {
            gO->Update();
        }
    }

    Scene::Scene() {
        mSceneSettings = new SceneSettings();

    }

    Scene::Scene(SceneSettings * settings) {
        mSceneSettings = settings;

        //Create all objects in the settings
    }

}