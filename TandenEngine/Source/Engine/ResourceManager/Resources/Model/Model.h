//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_MODEL_H
#define TANDENENGINE_MODEL_H

#include <vulkan/vulkan.h>
#include <vector>

#include "MeshVertex.h"
#include "../Resource.h"
#include "../../BufferManager/Buffer.h"
class MeshVertex;

namespace TandenEngine {

    class Model : public Resource{
     public:
        Buffer mVertexBuffer;
        Buffer mIndexBuffer;

        Model();

        std::vector<MeshVertex> mVertices = {};
        std::vector<uint16_t> mIndices;

        // VkBuffer vertexBuffer;
        static bool CheckIfSupported(std::string extension);
        void CreateVertexBuffer();

        Model(MetaData* inputData);  // Create a model resource from meta data input

     private:
        void LoadModel();
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_MODEL_H
