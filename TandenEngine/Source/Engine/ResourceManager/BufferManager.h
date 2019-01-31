//
// Created by rosser.martinez on 1/30/2019.
//

#ifndef TANDENENGINE_BUFFERMANAGER_H
#define TANDENENGINE_BUFFERMANAGER_H

#include "../RenderingSystem/RenderingSystem.h"
#include <vulkan/vulkan.h>
#include "../ResourceManager/Resources/Model/Model.h"
#include <vector>

namespace TandenEngine {

    class BufferManager {

        static std::vector<MeshVertex> mVertices;

    public:


        static void CreateVertexBufferForModel(Model *targetModel)
        {
            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = sizeof(mVertices[0]) * mVertices.size(); //TODO change mVertices to target models vertices
            bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

            if (vkCreateBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice, &bufferInfo, nullptr, &targetModel->vertexBuffer) != VK_SUCCESS) {
                throw std::runtime_error("failed to create vertex buffer!");
            }
        }


    };

}

#endif //TANDENENGINE_BUFFERMANAGER_H
