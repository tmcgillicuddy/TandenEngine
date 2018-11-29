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
            case DataType::SCENE:
                newResource = new Model();
                break;
            case DataType::MATERIAL:
                newResource = new Material();
                break;
            case DataType::MODEL:
                newResource = new Model();
                break;
            case DataType::AUDIO:
                newResource = new AudioClip();
                break;
            case DataType::IMAGE:
                newResource = new Image();
                break;
            case DataType::SHADER:
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

    void ResourceManager::AddResource(Resource *newResouce, MetaData *newMetaData) {
        mResourceFiles.emplace_back(newResouce);
        mMetaData.emplace_back(newMetaData);
    }

    void ResourceManager::AddResource(Resource *newResouce) {


        mResourceFiles.emplace_back(newResouce);
    }

    void ResourceManager::SaveProjectResources() {

    }
}