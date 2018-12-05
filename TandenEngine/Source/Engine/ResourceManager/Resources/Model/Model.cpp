//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Model.h"

namespace TandenEngine {

<<<<<<< HEAD
    Model::Model():Resource(ResourceType::MODEL) {
=======
    Model::Model() {
        mResourceType = ResourceType::MODEL;
    }
>>>>>>> 9949ff049a91c7bc254c1247e311112fe9b0d162

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }
}