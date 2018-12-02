//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "ResourceManager.h"
namespace TandenEngine {

    std::vector<Resource *> ResourceManager::mResourceFiles;
    std::vector<MetaData*> ResourceManager::mMetaData;

    Resource * ResourceManager::GenerateResourceFromMetaData(MetaData *metaData) {
        Resource * newResource = nullptr;
        switch (metaData->mFileType)
        {
            case ResourceType::SCENE:
                std::cout<<"Creating Scene\n";
                newResource = new Scene(metaData);
                break;
            case ResourceType::PREFAB:
                std::cout<<"Creating Prefab\n";
                newResource = new Prefab();
                break;
            case ResourceType::MATERIAL:
                std::cout<<"Creating Material\n";
                newResource = new Material();
                break;
            case ResourceType::MODEL:
                std::cout<<"Creating Model\n";
                newResource = new Model();
                break;
            case ResourceType::AUDIO:
                std::cout<<"Creating Audio\n";
                newResource = new AudioClip();
                break;
            case ResourceType::IMAGE:
                std::cout<<"Creating Image\n";
                newResource = new Image();
                break;
            case ResourceType::SHADER:
                std::cout<<"Creating Shader\n";
                newResource = new Shader();
                break;
            default:
                break;
        }
        return newResource;
    }

    void ResourceManager::ImportAssetsFolder() {
        std::vector<std::string> filePaths;
        //Get list of all file paths from existing meta files
        for(MetaData * data : mMetaData)
        {
            filePaths.emplace_back(data->mFileDir);
        }
        //Get all files that are not of type .meta


        //Create new meta file for any filepath that isn't part of the filePaths vector


    }

    void ResourceManager::AddResource(Resource *newResource, MetaData *newMetaData) {
        mResourceFiles.emplace_back(newResource);
        mMetaData.emplace_back(newMetaData);
    }

    void ResourceManager::AddResource(Resource *newResource) {
        MetaData * newData = new MetaData();
        newData->mFileName = newResource->fileName;
        newData->mFileType = newResource->mResourceType;
        newData->mFileDir = Serializer::mProjectDir +"/Assets/"+ newResource->GenerateFileName();

        Serializer::WriteStringToAssetFolder(newResource->fileName + ".meta", newData->ConvertToString());

        mResourceFiles.emplace_back(newResource);
    }

    void ResourceManager::AddMetaData(MetaData *newMetaData) {
        mMetaData.emplace_back(newMetaData);
    }

    void ResourceManager::GenerateNewMetaData(Resource *newResource) {
        MetaData * newData = new MetaData();
        newData->mFileName = newResource->fileName;
        newData->mFileType = newResource->mResourceType;
        newData->mFileDir = Serializer::mProjectDir +"/Assets/"+ newResource->GenerateFileName();

        Serializer::WriteStringToAssetFolder(newResource->fileName + ".meta", newData->ConvertToString());
    }
}