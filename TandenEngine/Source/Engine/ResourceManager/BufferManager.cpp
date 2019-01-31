//
// Created by rosser.martinez on 1/30/2019.
//

#include "BufferManager.h"

namespace TandenEngine {

    std::vector<MeshVertex> BufferManager::mVertices = {
        MeshVertex(Vector3(0.0f, -0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
        MeshVertex(Vector3(0.5f, 0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
        MeshVertex(Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f))
    };

}