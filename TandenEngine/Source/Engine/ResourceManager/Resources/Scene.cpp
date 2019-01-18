//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Scene.h"
#include "../../Serialization/Serializer.h"
#include "../ResourceManager.h"

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
        //std::cout << "Updating Scene \n";
        for (const auto &gO : mGameObjects) {
            gO->Update();
        }
    }

    Scene::Scene() {
        fileName = "UntitledScene";
        mResourceType = ResourceType::SCENE;
    }

    void Scene::SaveScene() {
        std::string data = fileName + "\n";

        for (const auto &gO : mGameObjects)
        {
            data += gO->ToString();
            data += "-----\n";
        }

        Serializer::WriteStringToAssetFolder(fileName+".scene", data);
        ResourceManager::GenerateNewMetaData(this);
    }

    Scene::Scene(MetaData *inputMeta) {
        mResourceType = ResourceType::SCENE;
        mMetaData = inputMeta;
        std::string data = Serializer::GetFileData(inputMeta->mFileDir);
        std::vector<std::string> dataLines = Serializer::SeperateString(data);
        fileName = dataLines[0];
        for(size_t i=1; i < dataLines.size(); ++i) //Run through every object in the scene and generate a new gameobject for it
        {
            std::vector<std::string> goData;
            goData.emplace_back(dataLines[i]);
            ++i;
            while(i < dataLines.size() && dataLines[i] != "-----") //Until the end of this object
            {
                goData.emplace_back(dataLines[i]); //Add it to the object
                ++i;
            }
            GameObject * newGo = new GameObject();
            newGo->GenerateFromData(goData);
            mGameObjects.emplace_back(newGo);
        }
    }

    bool Scene::CheckIfSupported(std::string extension) {
       return (extension == ".scene");
    }
}