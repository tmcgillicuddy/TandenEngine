//
// Created by Thomas on 1/19/2019.
//

#include "CubeModel.h"

namespace TandenEngine {
    CubeModel::CubeModel() {
        // TODO(Anyone) implement logic for creating a model with cube vertices
        mVertices = {
            MeshVertex(vec3(-0.5f, -0.5f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(0.5f, -0.5f, 0.0f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(0.5f, 0.5f, 0.0f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, 0.0f), vec3(0.66f, 0.3f, 0.1f))
        };

        mIndices = {
                0, 1, 2, 2, 3, 0
        };
    }
}  // namespace TandenEngine
