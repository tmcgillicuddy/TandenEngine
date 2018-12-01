//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "ResourceManager.h"
namespace TandenEngine {

    std::vector<Resource *> ResourceManager::mResourceFiles;
    std::vector<MetaData*> ResourceManager::mMetaData;

    Resource * ResourceManager::GenerateResourceFromMetaData(MetaData *metaData) {
        Resource * newResource = nullptr;
        std::cout<<metaData->mFileType;
        switch (metaData->mFileType)
        {
            case DataType::SCENE:
                std::cout<<"Creating Scene";
                newResource = new Scene();
                break;
            case DataType::MATERIAL:
                std::cout<<"Creating Material";
                newResource = new Material();
                break;
            case DataType::MODEL:
                std::cout<<"Creating Model";
                newResource = new Model();
                break;
            case DataType::AUDIO:
                std::cout<<"Creating Audio";
                newResource = new AudioClip();
                break;
            case DataType::IMAGE:
                std::cout<<"Creating Image";
                newResource = new Image();
                break;
            case DataType::SHADER:
                std::cout<<"Creating Shader";
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
        newData->mFileType = newResource->mResourceType;
        newData->mFileDir = Serializer::mProjectDir +"/Assets/"+ newResource->GenerateFileName();

        Serializer::WriteStringToAssetFolder(newResource->fileName + ".meta", newData->ConvertToString());

        mResourceFiles.emplace_back(newResource);
    }
}