//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Scene.h"
#include "../../Serialization/Serializer.h"

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

    Scene::Scene() : Resource(DataType::SCENE) {
        fileName = "UntitledScene";
        mResourceType = DataType::SCENE;
    }

    void Scene::SaveScene() {
        std::string data = fileName + "\n";

        for (const auto &gO : mGameObjects)
        {
            data += gO->ToString();
            data += "-----\n";
        }

        Serializer::WriteStringToAssetFolder(fileName+".scene", data);
    }

}