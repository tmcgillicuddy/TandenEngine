//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Prefab.h"
#include "../../Serialization/Serializer.h"
#include "../ResourceManager.h"

namespace TandenEngine {

    void Prefab::CreatePrefab(GameObject *sourceGO) {
        fileName = sourceGO->mName;
        mComponents.reserve(sourceGO->mComponents.size());
        for(const auto &comp : sourceGO->mComponents)
        {
            mComponents.push_back(comp->Clone());
        }


        SavePrefab();
        //TODO destroy source go and replace with prefab reference
    }

    void Prefab::SavePrefab() {
        std::string data = fileName + "\n";
        for (const auto &component : mComponents)
        {
            data += component->ToString();
            data += "---\n";
        }

        Serializer::WriteStringToAssetFolder(fileName+".prefab", data);
        ResourceManager::GenerateNewMetaData(this);
    }

    Prefab::Prefab(): Resource(ResourceType::PREFAB) {
        fileName = "UntitledPrefab";
        mResourceType = ResourceType::PREFAB;
    }

    void Prefab::UpdatePrefab(GameObject *sourceGO) {

    }

    Prefab::Prefab(MetaData *metaData): Resource(ResourceType::PREFAB) {
        mResourceType = ResourceType::PREFAB;
        std::string data = Serializer::GetFileData(metaData->mFileDir);
        std::vector<std::string> dataLines = Serializer::SeperateString(data);
        GameObject * templateGo = new GameObject();
        templateGo->GenerateFromData(dataLines); //Create a template gameobject from the meta data normally
        CreatePrefab(templateGo); //Copy that gameobject's info normally
    }

    bool Prefab::CheckIfSupported(std::string extension) {
        return (extension == ".prefab");
    }

}