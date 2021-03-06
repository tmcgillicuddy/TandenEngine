//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "ResourceManager.h"
#include "Resources/Model/Primitive.h"
namespace TandenEngine {

    std::vector<Resource *> ResourceManager::mResourceFiles;
    std::vector<MetaData*> ResourceManager::mMetaData;

    Resource * ResourceManager::GenerateResourceFromMetaData(MetaData *metaData) {
        Resource * newResource = nullptr;
        switch (metaData->mFileType) {
            case ResourceType::SCENE:
                std::cout <<"Creating Scene\n";
                newResource = new Scene(metaData);
                break;
            case ResourceType::PREFAB:
                std::cout <<"Creating Prefab\n";
                newResource = new Prefab(metaData);
                break;
            case ResourceType::MATERIAL:
                std::cout <<"Creating Material\n";
                newResource = new Material(metaData);
                break;
            case ResourceType::MODEL:
                std::cout <<"Creating Model\n";
                newResource = new Model(metaData);
                break;
            case ResourceType::AUDIO:
                std::cout <<"Creating Audio\n";
                newResource = new AudioClip(metaData);
                break;
            case ResourceType::IMAGE:
                std::cout <<"Creating Image\n";
                newResource = new Image(metaData);
                break;
            case ResourceType::SHADER:
                std::cout <<"Creating Shader\n";
                newResource = new Shader(metaData);
                break;
            case ResourceType::FONT:
                std::cout <<"Creating Font\n";
                newResource = new Font(metaData);
                break;
            default:
                break;
        }
        return newResource;
    }

    void ResourceManager::ImportAssetsFolder() {
        // Init any default assets
        Primitive::InitPrimitives();

        std::vector<std::string> filePaths;
        // Get list of all file paths from existing meta files
        for (MetaData * data : mMetaData) {
            filePaths.emplace_back(data->mFileDir);
        }
        // Get all files that are not of type .meta


        // Create new meta file for any filepath that isn't part of the filePaths vector
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

        Serializer::WriteStringToAssetFolder(newResource->fileName + ".meta",
                newData->ConvertToString());

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

        Serializer::WriteStringToAssetFolder(newResource->fileName + ".meta",
                newData->ConvertToString());
    }

    std::vector<std::string> ResourceManager::GetAllFoundResourceFiles() {
        std::vector<std::string> files;
        for (auto file : mMetaData) {
            std::string tempName = file->mFileDir;
            std::replace(tempName.begin(), tempName.end(), '/', '\\');
            files.emplace_back(tempName);
        }

        return files;
    }

    ResourceType ResourceManager::CheckExtensionSupported(std::string extension) {
        if (Scene::CheckIfSupported(extension))
            return ResourceType::SCENE;
        if (Prefab::CheckIfSupported(extension))
            return ResourceType::PREFAB;
        if (Material::CheckIfSupported(extension))
            return ResourceType::MATERIAL;
        if (Image::CheckIfSupported(extension))
            return ResourceType::IMAGE;
        if (Model::CheckIfSupported(extension))
            return ResourceType::MODEL;
        if (Shader::CheckIfSupported(extension))
            return ResourceType::SHADER;
        if (AudioClip::CheckIfSupported(extension))
            return ResourceType::AUDIO;
        if (Font::CheckIfSupported(extension))
            return ResourceType::FONT;

        return ResourceType::INVALID;
    }

    void ResourceManager::GenerateNewMetaData(std::string path, ResourceType type) {
        MetaData * newData = new MetaData();
        size_t lastindex = path.find_last_of(".");
        std::string fileName = path.substr(0, lastindex);
        newData->mFileName = fileName;
        newData->mFileType = type;
        newData->mFileDir = Serializer::mProjectDir +"/Assets/"+ path;

        // Save the meta data file
        Serializer::WriteStringToAssetFolder(fileName + ".meta", newData->ConvertToString());

        // Test generate resource from meta data
        Resource * newResouce = GenerateResourceFromMetaData(newData);
        if (newResouce != nullptr) {
            // Add meta data to resource manager to track
            AddMetaData(newData);
        } else {
            std::cout << "Couldn't generate resource from meta data: " << fileName << std::endl;
        }
    }
}  // namespace TandenEngine
