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

        static std::vector<MeshVertex> mVertices; //test vertices

        //consider eventually storing all the necessary vkBuffers and vkDeviceMemory here
        static VkDeviceMemory vBufferMemory;

        static std::vector<VkBuffer> mBufferList;

        static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        static void CreateVertexBufferForModel(Model * targetModel);

        static void CreateVertexBufferForTargetModel(Model * targetModel);

    };

}

#endif //TANDENENGINE_BUFFERMANAGER_H
