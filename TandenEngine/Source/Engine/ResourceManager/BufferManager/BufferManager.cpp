//
// Created by rosser.martinez on 1/30/2019.
//

#include "BufferManager.h"
#include <vulkan/vulkan.h>


#include "Debug.h"

namespace TandenEngine {
    // TODO(Rosser) Deprecate
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
    }

    VkResult BufferManager::CreateBuffer(VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlags,
                                         Buffer *buffer, VkDeviceSize size, void *data) {
        VulkanInfo vInfo = *RenderingSystem::GetVulkanInfo();
        buffer->mDevice = vInfo.logicalDevice;

        // Create the buffer handle
        VkBufferCreateInfo bufferCreateInfo = {};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.usage = usageFlags;
        bufferCreateInfo.size = size;
        Debug::CheckVKResult(vkCreateBuffer(vInfo.logicalDevice, &bufferCreateInfo, nullptr, &buffer->mBuffer));

        // Create the memory backing up the buffer handle
        VkMemoryRequirements memReqs;
        VkMemoryAllocateInfo memAlloc = {};
        memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        vkGetBufferMemoryRequirements(vInfo.logicalDevice, buffer->mBuffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        // Find a memory type index that fits the properties of the buffer
        memAlloc.memoryTypeIndex = vInfo.GetMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);
        Debug::CheckVKResult(vkAllocateMemory(vInfo.logicalDevice, &memAlloc, nullptr, &buffer->mMemory));

        buffer->mAlignment = memReqs.alignment;
        buffer->mSize = memAlloc.allocationSize;
        buffer->mUsageFlags = usageFlags;
        buffer->mMemoryPropertyFlags = memoryPropertyFlags;

        // If a pointer to the buffer data has been passed, map the buffer and copy over the data
        if (data != nullptr)
        {
            Debug::CheckVKResult(buffer->map());
            memcpy(buffer->mMapped, data, size);
            if ((memoryPropertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) == 0)
                buffer->flush();

            buffer->unmap();
        }

        // Initialize a default descriptor that covers the whole buffer size
        buffer->setupDescriptor();

        // Attach the memory to the buffer object
        return buffer->bind();
    }
}  // namespace TandenEngine
