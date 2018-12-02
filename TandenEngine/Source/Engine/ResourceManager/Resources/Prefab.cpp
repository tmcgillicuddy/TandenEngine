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

}