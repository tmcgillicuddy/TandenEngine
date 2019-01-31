//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Model.h"
#include "../../BufferManager.h"

namespace TandenEngine {

    Model::Model() {
        mResourceType = ResourceType::MODEL;

        BufferManager::CreateVertexBufferForModel(this);
    }

    bool Model::CheckIfSupported(std::string extension) {
        return (extension == ".fbx" || extension == ".obj");
    }
}