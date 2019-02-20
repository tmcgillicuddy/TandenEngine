//
// Created by rosser.martinez on 1/30/2019.
//

#ifndef TANDENENGINE_BUFFERMANAGER_H
#define TANDENENGINE_BUFFERMANAGER_H

#include <vulkan/vulkan.h>
#include <vector>

#include "../../RenderingSystem/RenderingSystem.h"
#include "../Resources/Model/Model.h"
#include "../Resources/Model/MeshVertex.h"
#include "../Resources/Model/Model.h"

#include "NilsMath.h"


namespace TandenEngine {

    class MeshVertex;
    class Model;

    struct UniformBufferObject {
        mat4 model;
        mat4 view;
        mat4 proj;
    };

    class BufferManager {
     public:
        static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

        static void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

        static void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        static void CreateStagingBuffer();

        static void CreateDescriptorSetLayout();

        static void Cleanup();

        // General Init buffer function
        static VkResult CreateBuffer(VkBufferUsageFlags usageFlags,
                VkMemoryPropertyFlags memoryPropertyFlags, Buffer *buffer,
                VkDeviceSize size, void *data = nullptr);
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_BUFFERMANAGER_H
