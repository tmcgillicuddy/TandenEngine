//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Resource.h"

namespace TandenEngine {
    std::string Resource::GenerateFileName() {
        std::string newName = fileName;

        switch (mResourceType) {
            case ResourceType::SCENE:
                newName += ".scene";
                break;
            case ResourceType::PREFAB:
                newName += ".prefab";
                break;
            case ResourceType::MATERIAL:
                newName += ".material";
                break;
        }

        return newName;
    }
}  // namespace TandenEngine
