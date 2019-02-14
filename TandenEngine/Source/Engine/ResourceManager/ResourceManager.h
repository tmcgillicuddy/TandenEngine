//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_RESOURCEMANAGER_H
#define TANDENENGINE_RESOURCEMANAGER_H

#include "Resources/ResourceHeader.h"
#include "../Serialization/Serializer.h"


namespace TandenEngine {
    class ResourceManager {
     private:
        // Loaded resource files
        static std::vector<Resource*> mResourceFiles;
        // Loaded meta data files for loaded scenes
        static std::vector<MetaData*> mLoadedMetaData;
        // All meta data files in project
        static std::vector<MetaData*> mMetaData;

     public:
        static Resource* GenerateResourceFromMetaData(MetaData * metaData);

        // Generate new meta data for any files in the assets folder
        static void ImportAssetsFolder();

        // When adding a resource that was generated from meta data
        static void AddResource(Resource * newResouce, MetaData* newMetaData);
        // When adding a NEW resource and need to generate new meta data
        // (discovered new file, new scene/prefab/material file created and saved)
        static void AddResource(Resource * newResouce);
        // Adds to the meta data vector to track loaded files
        static void AddMetaData(MetaData * newMetaData);
        // Makes meta data but doesn't allocate the resource
        static void GenerateNewMetaData(Resource * newResource);
        static void GenerateNewMetaData(std::string path, ResourceType type);
        // Returns a list of all the resource file there are already meta data for
        static std::vector<std::string> GetAllFoundResourceFiles();
        // Checks if input extension is supported by any resource
        // and returns the resource type it would be
        static ResourceType CheckExtensionSupported(std::string);
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_RESOURCEMANAGER_H
