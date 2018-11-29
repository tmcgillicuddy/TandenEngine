//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_RESOURCEMANAGER_H
#define TANDENENGINE_RESOURCEMANAGER_H

#include "Resources/Resource.h"
#include "Resources/Shader.h"
#include "Resources/Material.h"
#include "Resources/Image.h"
#include "Resources/Prefab.h"
#include "Resources/AudioClip.h"
#include "Resources/Model/Model.h"
#include "../Serialization/Serializer.h"

namespace TandenEngine {
    class ResourceManager {
    private:
        static std::vector<Resource*> mResourceFiles;
        static std::vector<MetaData*> mMetaData;
    public:
        static Resource* GenerateResourceFromMetaData(MetaData * metaData);

        static void ImportAssetsFolder(); //Generate new meta data for any files in the assets folder

        static void AddResource(Resource * newResouce, MetaData* newMetaData);
        static void AddResource(Resource * newResouce); //When making a resource and need to generate new meta data
        static void SaveProjectResources();

    };
}

#endif //TANDENENGINE_RESOURCEMANAGER_H
