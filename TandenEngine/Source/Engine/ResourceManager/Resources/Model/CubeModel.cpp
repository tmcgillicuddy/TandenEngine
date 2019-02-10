//
// Created by Thomas on 1/19/2019.
//

#include "CubeModel.h"

namespace TandenEngine {
    CubeModel::CubeModel() {
        // TODO(Anyone) implement logic for creating a model with cube vertices
        mVertices = {
            MeshVertex(vec3(-0.5f, -0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.66f, 0.3f, 0.1f)),

            MeshVertex(vec3(0.5f, -0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(0.5f, 0.5f, 0.5f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.66f, 0.3f, 0.1f)),

            MeshVertex(vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(0.5f, -0.5f, -0.5f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.66f, 0.3f, 0.1f)),

            MeshVertex(vec3(0.5f, -0.5f, -0.5f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(-0.5f, -0.5f, 0.5f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(-0.5f, -0.5f, -0.5f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.66f, 0.3f, 0.1f)),

            MeshVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, -0.5f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(0.5f, 0.5f, -0.5f), vec3(0.66f, 0.3f, 0.1f)),

            MeshVertex(vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 0.0f, 0.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.66f, 0.1f, 1.0f)),
            MeshVertex(vec3(0.5f, -0.5f, 0.5f), vec3(0.36f, 1.0f, 1.0f)),
            MeshVertex(vec3(-0.5f, 0.5f, 0.5f), vec3(0.66f, 0.3f, 0.1f)),
        };

        mIndices = {
                1, 2, 0, // Front
                3, 6, 8,
                7, 4, 9, // Back
                5, 10, 11,
                12, 13, 14, // Top
                15, 16, 17,
                1, 18, 2, // Bottom
                3, 19, 6,
                7, 20, 4, // Left
                5, 21, 10,
                12, 22, 13, // Right
                15, 23, 16,
        };
    }
}  // namespace TandenEngine
