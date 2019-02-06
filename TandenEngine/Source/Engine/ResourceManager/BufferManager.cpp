//
// Created by rosser.martinez on 1/30/2019.
//

#include "BufferManager.h"
#include <vulkan/vulkan.h>
#include "Debug.h"

namespace TandenEngine {

    std::vector<MeshVertex> BufferManager::mVertices = {
        MeshVertex(vec3(-0.5f, -0.5f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
        MeshVertex(vec3(0.5f, -0.5f, 0.0f), vec3(0.66f, 0.1f, 1.0f)),
        MeshVertex(vec3(0.5f, 0.5f, 0.0f), vec3(0.36f, 1.0f, 1.0f)),
        MeshVertex(vec3(-0.5f, 0.5f, 0.0f), vec3(0.66f, 0.3f, 0.1f))
    };

    std::vector<uint16_t> BufferManager::mIndices = {
            0, 1, 2, 2, 3, 0
    };

    std::vector<VkDeviceMemory> BufferManager::mVertexBufferMemoryList;
    std::vector<VkDeviceMemory> BufferManager::mIndexBufferMemoryList;
    std::vector<VkBuffer> BufferManager::mVertexBufferList;
    std::vector<VkBuffer> BufferManager::mIndexBufferList;

    Model* BufferManager::testModel;

    void BufferManager::AddVertexBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory) {
        mVertexBufferList.push_back(newBuffer);
        mVertexBufferMemoryList.push_back(newDeviceMemory);
    }

    void BufferManager::AddIndexBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory) {
        mIndexBufferList.push_back(newBuffer);
        mIndexBufferMemoryList.push_back(newDeviceMemory);
    }

    void BufferManager::CreateVertexBufferForTargetModel() {
        // TODO(Rosser) temporarily set local verts (REMOVE THIS AND LOCAL VERTS FROM MODEL
        // BufferManager::testModel->mLocalVertices = mVertices;

        // TODO(Rosser) replace references of [0], we may have multiple objects
        VkDeviceSize bufferSize = sizeof(mVertices[0]) * mVertices.size();

        // created locally and then trashed forever after creating the VB
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        // create staging buffer
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBuffer, stagingBufferMemory);

        // write staging buffer to memory
        void* data;
        vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, mVertices.data(), (size_t) bufferSize);
        vkUnmapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory);

        // create memory for new vertex buffer
        VkBuffer newVertexBuffer;
        VkDeviceMemory newVertexBufferMemory;

        // create vertex buffer
        CreateBuffer(bufferSize,
                VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, newVertexBuffer, newVertexBufferMemory);

        // add vertex buffer and memory to list
        AddVertexBuffer(newVertexBuffer, newVertexBufferMemory);

        // copy data from staging to vertex buffer
        CopyBuffer(stagingBuffer, newVertexBuffer, bufferSize);

        // cleanup
        vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBuffer, nullptr);
        vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory, nullptr);
    }

    void BufferManager::CreateIndexBufferForTargetModel() {
        // TODO(Rosser) temporarily set local verts (REMOVE THIS AND LOCAL VERTS FROM MODEL
        // BufferManager::testModel->mLocalVertices = mVertices;

        // TODO(Rosser) replace references of [0], we may have multiple objects
        VkDeviceSize bufferSize = sizeof(mIndices[0]) * mIndices.size();

        // created locally and then trashed forever after creating the VB
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        // create staging buffer
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                stagingBuffer, stagingBufferMemory);

        // write staging buffer to memory
        void* data;
        vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, mIndices.data(), (size_t) bufferSize);
        vkUnmapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory);

        // create memory for new vertex buffer
        VkBuffer newIndexBuffer;
        VkDeviceMemory newIndexBufferMemory;

        // create vertex buffer
        CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT |
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
        newIndexBuffer, newIndexBufferMemory);

        // add vertex buffer and memory to list
        AddIndexBuffer(newIndexBuffer, newIndexBufferMemory);

        // copy data from staging to vertex buffer
        CopyBuffer(stagingBuffer, newIndexBuffer, bufferSize);

        // cleanup
        vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBuffer, nullptr);
        vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory, nullptr);
    }

    void BufferManager::CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice,
                &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create buffer!");
        }

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(RenderingSystem::GetVulkanInfo()->logicalDevice,
                buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate buffer memory!");
        }

        vkBindBufferMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                buffer, bufferMemory, 0);
    }

    uint32_t BufferManager::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        // get properties of physical device memory
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(RenderingSystem::GetVulkanInfo()->physicalDevice,
                &memProperties);

        // iterate through physical memory for suitable memory types for specified properties
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i))
                && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void BufferManager::CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
        // allocation info
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = RenderingSystem::GetVulkanInfo()->commandPool;
        allocInfo.commandBufferCount = 1;

        // need command buffers for memory transfer operations, create temp one for copy
        VkCommandBuffer commandBuffer;

        // allocate command buffers
        vkAllocateCommandBuffers(RenderingSystem::GetVulkanInfo()->logicalDevice,
                &allocInfo, &commandBuffer);

        // start recording
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        // copy
        VkBufferCopy copyRegion = {};
        copyRegion.size = size;
        vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

        // end copy
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        // submit to queue and wait
        vkQueueSubmit(RenderingSystem::GetVulkanInfo()->gfxQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(RenderingSystem::GetVulkanInfo()->gfxQueue);

        // cleanup
        vkFreeCommandBuffers(RenderingSystem::GetVulkanInfo()->logicalDevice,
                RenderingSystem::GetVulkanInfo()->commandPool, 1, &commandBuffer);
    }


    void BufferManager::Cleanup() {
        for (int i = 0; i < mVertexBufferMemoryList.size(); ++i) {
            // vertex buffers
            vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    mVertexBufferList[i], nullptr);
            vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    mVertexBufferMemoryList[i], nullptr);

            // index buffers
            vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    mVertexBufferList[i], nullptr);
            vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    mVertexBufferMemoryList[i], nullptr);
        }
    }
}  // namespace TandenEngine