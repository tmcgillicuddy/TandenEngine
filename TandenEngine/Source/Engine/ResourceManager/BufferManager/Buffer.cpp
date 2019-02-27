//
// Created by rosser.martinez on 2/17/2019.
//

#include "Buffer.h"
#include "../../RenderingSystem/VulkanInfo.h"

namespace TandenEngine {

    void Buffer::destroy() {
        if (mBuffer) {
            vkDestroyBuffer(mDevice, mBuffer, nullptr);
        }

        if (mMemory) {
            vkFreeMemory(mDevice, mMemory, nullptr);
        }
    }

    VkResult Buffer::flush(VkDeviceSize size, VkDeviceSize offset) {
        VkMappedMemoryRange mappedRange = {};
        mappedRange.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
        mappedRange.memory = mMemory;
        mappedRange.offset = offset;
        mappedRange.size = size;
        return vkFlushMappedMemoryRanges(mDevice, 1, &mappedRange);
    }

    void Buffer::CopyBufferTo(Buffer *destination) {

        VulkanInfo vkInfo = *RenderingSystem::GetVulkanInfo();

        // allocation info
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = vkInfo.commandPool;
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
        copyRegion.size = mMemory;
        vkCmdCopyBuffer(commandBuffer, this->mBuffer, destination->mBuffer, 1, &copyRegion);

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


}  // namespace TandenEngine
