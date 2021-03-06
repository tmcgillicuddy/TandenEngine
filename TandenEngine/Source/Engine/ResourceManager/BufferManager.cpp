//
// Created by rosser.martinez on 1/30/2019.
//

#include "BufferManager.h"
#include <vulkan/vulkan.h>


#include "Debug.h"

namespace TandenEngine {
    std::vector<VkDeviceMemory> BufferManager::mVertexBufferMemoryList;
    std::vector<VkDeviceMemory> BufferManager::mIndexBufferMemoryList;
    std::vector<VkDeviceMemory> BufferManager::mUniformBufferMemoryList;
    std::vector<VkBuffer> BufferManager::mVertexBufferList;
    std::vector<VkBuffer> BufferManager::mIndexBufferList;
    std::vector<VkBuffer> BufferManager::mUniformBufferList;


    std::vector<Model*> BufferManager::modelList;

    void BufferManager::AddVertexBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory) {
        mVertexBufferList.push_back(newBuffer);
        mVertexBufferMemoryList.push_back(newDeviceMemory);
    }

    void BufferManager::AddIndexBuffer(VkBuffer newBuffer, VkDeviceMemory newDeviceMemory) {
        mIndexBufferList.push_back(newBuffer);
        mIndexBufferMemoryList.push_back(newDeviceMemory);
    }

    void BufferManager::CreateVertexBufferForTargetModel() {
        for (auto targetModel : modelList) {
            VkDeviceSize bufferSize = sizeof(targetModel->mVertices[0])
                    * targetModel->mVertices.size();

            // created locally and then trashed forever after creating the VB
            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;

            // create staging buffer
            CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         stagingBuffer, stagingBufferMemory);
            std::cout << "Test";

            // write staging buffer to memory
            void *data;
            vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                        stagingBufferMemory, 0, bufferSize, 0, &data);
            memcpy(data, targetModel->mVertices.data(), (size_t) bufferSize);
            vkUnmapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice, stagingBufferMemory);

            // create memory for new vertex buffer
            VkBuffer newVertexBuffer;
            VkDeviceMemory newVertexBufferMemory;

            // create vertex buffer
            CreateBuffer(bufferSize,
                         VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                         VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, newVertexBuffer,
                         newVertexBufferMemory);

            // add vertex buffer and memory to list
            AddVertexBuffer(newVertexBuffer, newVertexBufferMemory);

            // copy data from staging to vertex buffer
            CopyBuffer(stagingBuffer, newVertexBuffer, bufferSize);

            // cleanup
            vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    stagingBuffer, nullptr);
            vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    stagingBufferMemory, nullptr);
        }
    }

    void BufferManager::CreateIndexBufferForTargetModel() {
        for (auto targetModel : modelList) {
            VkDeviceSize bufferSize = sizeof(uint16_t) * targetModel->mIndices.size();

            // created locally and then trashed forever after creating the VB
            VkBuffer stagingBuffer;
            VkDeviceMemory stagingBufferMemory;

            // create staging buffer
            CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                         VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                         stagingBuffer, stagingBufferMemory);

            // write staging buffer to memory
            void *data;
            vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                        stagingBufferMemory, 0, bufferSize, 0, &data);
            memcpy(data, targetModel->mIndices.data(), (size_t) bufferSize);
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
            vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    stagingBuffer, nullptr);
            vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    stagingBufferMemory, nullptr);
        }
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




    void BufferManager::CreateUniformBuffers() {
        // resize to size of swapchains
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        mUniformBufferList.resize(RenderingSystem::GetVulkanInfo()->swapChainImages.size());
        mUniformBufferMemoryList.resize(RenderingSystem::GetVulkanInfo()->swapChainImages.size());

        // create uniform buffers
        for (size_t i = 0; i < RenderingSystem::GetVulkanInfo()->swapChainImages.size(); i++) {
            CreateBuffer(bufferSize,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                    VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                    mUniformBufferList[i], mUniformBufferMemoryList[i]);
        }
    }

    void BufferManager::UpdateUniformBuffers(uint32_t currentImage) {
        // pass time
        static auto startTime = std::chrono::high_resolution_clock::now();
        // TODO(Rosser) Use our Timer class
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float,
        std::chrono::seconds::period>(currentTime - startTime).count();

        UniformBufferObject ubo = {};
        // TODO(Rosser) Add rotation, need radians, work with nils to figure this out
        // ubo.model = glm::rotate(glm::mat4(1.0f),
        // time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f),
        // glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        // ubo.proj = glm::perspective(glm::radians(45.0f),
        // RenderingSystem::GetVulkanInfo()->swapChainExtent.width /
        // (float) RenderingSystem::GetVulkanInfo()->swapChainExtent.height, 0.1f, 10.0f);
        // ubo.proj[1][1] *= -1;


        void* data;
        vkMapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                mUniformBufferMemoryList[currentImage], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                mUniformBufferMemoryList[currentImage]);
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

            // uniform buffers
            vkDestroyBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    mUniformBufferList[i], nullptr);
            vkFreeMemory(RenderingSystem::GetVulkanInfo()->logicalDevice,
                    mUniformBufferMemoryList[i], nullptr);
        }
    }
}  // namespace TandenEngine
