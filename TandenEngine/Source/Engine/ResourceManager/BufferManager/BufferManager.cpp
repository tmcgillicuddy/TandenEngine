//
// Created by rosser.martinez on 1/30/2019.
//

#include "BufferManager.h"
#include <vulkan/vulkan.h>


#include "Debug.h"

namespace TandenEngine {
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



    void BufferManager::Cleanup() {
    }

    VkResult BufferManager::CreateBuffer(VkBufferUsageFlags usageFlags,
                        VkMemoryPropertyFlags memoryPropertyFlags,
                        Buffer *buffer, VkDeviceSize size, void *data) {

        VulkanInfo vInfo = *RenderingSystem::GetVulkanInfo();
        buffer->mDevice = vInfo.logicalDevice;

        // Create the buffer handle
        VkBufferCreateInfo bufferCreateInfo = {};
        bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferCreateInfo.usage = usageFlags;
        bufferCreateInfo.size = size;
        Debug::CheckVKResult(vkCreateBuffer(vInfo.logicalDevice,
                &bufferCreateInfo, nullptr, &buffer->mBuffer));

        // Create the memory backing up the buffer handle
        VkMemoryRequirements memReqs;
        VkMemoryAllocateInfo memAlloc = {};
        memAlloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        vkGetBufferMemoryRequirements(vInfo.logicalDevice, buffer->mBuffer, &memReqs);
        memAlloc.allocationSize = memReqs.size;
        // Find a memory type index that fits the properties of the buffer
        memAlloc.memoryTypeIndex = FindMemoryType(memReqs.memoryTypeBits, memoryPropertyFlags);
        Debug::CheckVKResult(vkAllocateMemory(vInfo.logicalDevice,
                &memAlloc, nullptr, &buffer->mMemory));

        buffer->mAlignment = memReqs.alignment;
        buffer->mSize = memAlloc.allocationSize;
        buffer->mUsageFlags = usageFlags;
        buffer->mMemoryPropertyFlags = memoryPropertyFlags;

        // If a pointer to the buffer data has been passed, map the buffer and copy over the data
        if (data != nullptr) {
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

    void BufferManager::SetupDescriptorSet(VkDescriptorSet *dSet,
            VkDescriptorBufferInfo* bufferInfo) {

        VulkanInfo vInfo = *RenderingSystem::GetVulkanInfo();

        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = vInfo.descriptorPool;
        allocInfo.pSetLayouts = &vInfo.descriptorSetLayout;
        allocInfo.descriptorSetCount = 1;

        Debug::CheckVKResult(vkAllocateDescriptorSets(vInfo.logicalDevice, &allocInfo, dSet));

        // Binding 0 : Vertex shader uniform buffer
        VkWriteDescriptorSet writeDescriptorSet = {};
        writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writeDescriptorSet.dstSet = *dSet;
        writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        writeDescriptorSet.dstBinding = 0;
        writeDescriptorSet.pBufferInfo = bufferInfo;
        writeDescriptorSet.descriptorCount = 1;

        vkUpdateDescriptorSets(vInfo.logicalDevice, 1, &writeDescriptorSet, 0, NULL);
    }
}  // namespace TandenEngine
