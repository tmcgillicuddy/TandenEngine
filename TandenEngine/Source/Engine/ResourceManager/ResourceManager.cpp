//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "ResourceManager.h"
namespace TandenEngine {

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
}