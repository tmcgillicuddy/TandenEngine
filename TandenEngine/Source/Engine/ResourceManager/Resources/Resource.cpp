//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Resource.h"

namespace TandenEngine {
    std::string Resource::GenerateFileName() {
        std::string newName = fileName;

        switch(mResourceType)
        {
            case DataType::SCENE:
                newName += ".scene";
                break;
            case DataType::PREFAB:
                newName += ".prefab";
                break;
            case DataType::MATERIAL:
                newName += ".mat";
                break;
        }

        return newName;
    }
}