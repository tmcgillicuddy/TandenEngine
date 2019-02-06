//
// Created by rosser.martinez on 1/30/2019.
//

#ifndef TANDENENGINE_BUFFERMANAGER_H
#define TANDENENGINE_BUFFERMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>

#include "../RenderingSystem/RenderingSystem.h"
#include "../ResourceManager/Resources/Model/Model.h"
#include "Resources/Model/MeshVertex.h"
#include "Resources/Model/Model.h"


namespace TandenEngine {

    class MeshVertex;
    class Model;

    class BufferManager {
     public:
        static Model *testModel;
        static void setModel(Model * targetModel) {testModel = targetModel;}

        static std::vector<MeshVertex> mVertices;  // test vertices
        static std::vector<uint16_t> mIndices;     // test indices

        static std::vector<VkDeviceMemory> mVertexBufferMemoryList;
        static std::vector<VkDeviceMemory> mIndexBufferMemoryList;

        static std::vector<VkBuffer> mVertexBufferList;
        static std::vector<VkBuffer> mIndexBufferList;

        static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        static void AddVertexBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory);
        static void AddIndexBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory);

        static void CreateVertexBufferForModel(Model * targetModel);
        // TODO(Rosser) make this for target models, or all models that have been loaded
        static void CreateVertexBufferForTargetModel();
        static void CreateIndexBufferForTargetModel();

        static void CreateStagingBuffer();

        static void Cleanup();
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_BUFFERMANAGER_H
