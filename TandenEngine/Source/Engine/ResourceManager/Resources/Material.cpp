//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "Material.h"
#include "../ResourceManager.h"

namespace TandenEngine {

    Material::Material() : Resource(ResourceType::MATERIAL) {
        fileName = "UntitledMaterial";
        mResourceType = ResourceType::MATERIAL;
    }

    void Material::SaveMaterial() {
        std::string data = fileName + "\n";


        Serializer::WriteStringToAssetFolder(fileName+".material", data);
        ResourceManager::GenerateNewMetaData(this);
    }
}