//
// Created by rosser.martinez on 1/30/2019.
//

#ifndef TANDENENGINE_BUFFERMANAGER_H
#define TANDENENGINE_BUFFERMANAGER_H

#include "../RenderingSystem/RenderingSystem.h"
#include <vulkan/vulkan.h>
#include "../ResourceManager/Resources/Model/Model.h"
#include <vector>
#include "Resources/Model/MeshVertex.h"
#include "Resources/Model/Model.h"


namespace TandenEngine {

    class MeshVertex;
    class Model;


    class BufferManager {

    public:

        static Model *testModel;
        static void setModel(Model * targetModel){testModel = targetModel;};

        static std::vector<MeshVertex> mVertices; //test vertices

        static std::vector<VkDeviceMemory> mVertexBufferMemoryList;

        static std::vector<VkBuffer> mVertexBufferList;

        static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        static void AddBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory);

        static void CreateVertexBufferForModel(Model * targetModel);

        static void CreateVertexBufferForTargetModel(); //TODO make this for target models, or all models that have been loaded

        static void CreateStagingBuffer();

    };

}

#endif //TANDENENGINE_BUFFERMANAGER_H
