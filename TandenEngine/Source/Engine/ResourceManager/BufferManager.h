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

        std::vector<MeshVertex> mVertices = {
                MeshVertex(Vector3(0.0f, -0.5f, 0.0f), Vector3(1.0f, 0.0f, 0.0f)),
                MeshVertex(Vector3(0.5f, 0.5f, 0.0f), Vector3(0.0f, 1.0f, 0.0f)),
                MeshVertex(Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, 1.0f))
        };

    public:

        //only used for testing now, replace with actual models later
        //void InitVertices()
        //{
        //    MeshVertex newVertex1({0.0f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f});
        //    MeshVertex newVertex2({0.5f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f});
        //    MeshVertex newVertex3({-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f});
        //
        //    mVertices.push_back(newVertex1);
        //    mVertices.push_back(newVertex2);
        //    mVertices.push_back(newVertex3);
        //}


        static void CreateVertexBufferForModel(Model *targetModel)
        {
            VkBufferCreateInfo bufferInfo = {};
            bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
            bufferInfo.size = sizeof(vertices[0]) * vertices.size();
            bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
            bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;


            if (vkCreateBuffer(RenderingSystem::GetVulkanInfo()->logicalDevice, &bufferInfo, nullptr, &vertexBuffer) != VK_SUCCESS) {
                throw std::runtime_error("failed to create vertex buffer!");
            }
        }


    };

}

#endif //TANDENENGINE_BUFFERMANAGER_H
