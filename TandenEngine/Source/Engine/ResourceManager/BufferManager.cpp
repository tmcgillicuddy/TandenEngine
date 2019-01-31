//
// Created by rosser.martinez on 1/30/2019.
//

#include "BufferManager.h"
#include <vulkan/vulkan.h>

namespace TandenEngine {

    std::vector<MeshVertex> BufferManager::mVertices = {
        MeshVertex(Vector3(0.0f, -0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
        MeshVertex(Vector3(0.5f, 0.5f, 0.0f), Vector3(0.35f, 0.71f, 1.0f)),
        MeshVertex(Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.36f, 1.0f, 1.0f))
    };

    VkDeviceMemory BufferManager::vBufferMemory;
    std::vector<VkBuffer> BufferManager::mBufferList;



    void BufferManager::CreateVertexBufferForModel(Model * targetModel) //TODO pointer issues?
    {
        VkBufferCreateInfo bufferInfo = {};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = sizeof(mVertices[0]) * mVertices.size(); //TODO change mVertices to target models vertices
        bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        //temporarily set local verts (REMOVE THIS AND LOCAL VERTS FROM MODEL
        targetModel->mLocalVertices = mVertices;

        //create buffer, throw error on failure
        if (vkCreateBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice, &bufferInfo, nullptr, &mBufferList[0]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vertex buffer!");
        }

        //get memory requirements for the new buffer from logical device
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(RenderingSystem::GetVulkanInfo()->logicalDevice, mBufferList[0], &memRequirements);

        //specify size and type of memory requirements
        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        //allocate specified memory, throw on failure
        if (vkAllocateMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, &allocInfo, nullptr, &vBufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        //bind said memory to the models buffer
        vkBindBufferMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, mBufferList[0], vBufferMemory, 0);

        //map vertex data to memory
        void* data;
        vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, vBufferMemory, 0, bufferInfo.size, 0, &data);
        memcpy(data, mVertices.data(), (size_t) bufferInfo.size);
        vkUnmapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, vBufferMemory);

    }

    uint32_t BufferManager::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        //get properties of physical device memory
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(RenderingSystem::GetVulkanInfo()->physicalDevice, &memProperties);

        //iterate through physical memory for suitable memory types for specified properties
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }


}