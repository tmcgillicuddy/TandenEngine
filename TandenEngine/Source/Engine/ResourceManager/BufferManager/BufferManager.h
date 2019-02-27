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

        static void Cleanup();

        // General Init buffer function
        static VkResult CreateBuffer(VkBufferUsageFlags usageFlags,
                VkMemoryPropertyFlags memoryPropertyFlags, Buffer *buffer,
                VkDeviceSize size, void *data = nullptr);

        // General descriptor set Init function
        static void SetupDescriptorSet(VkDescriptorSet dSet, VkDescriptorBufferInfo* bufferInfo);
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_BUFFERMANAGER_H
