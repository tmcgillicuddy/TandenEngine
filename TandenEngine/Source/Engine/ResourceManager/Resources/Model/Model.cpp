//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Model.h"

namespace TandenEngine {

    Model::Model():Resource(ResourceType::MODEL) {

    }

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }
}