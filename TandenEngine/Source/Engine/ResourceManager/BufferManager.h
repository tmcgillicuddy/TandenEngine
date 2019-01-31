//
// Created by rosser.martinez on 1/30/2019.
//

#ifndef TANDENENGINE_BUFFERMANAGER_H
#define TANDENENGINE_BUFFERMANAGER_H

#include "../RenderingSystem/RenderingSystem.h"
#include <vulkan/vulkan.h>
#include "../ResourceManager/Resources/Model/Model.h"
#include <vector>
#include "Resources/Model/MeshVertex.h"
#include "Resources/Model/Model.h"

class MeshVertex;
class Model;

namespace TandenEngine {

    class BufferManager {

    public:

        static std::vector<MeshVertex> mVertices; //test vertices

        //consider eventually storing all the necessary vkBuffers and vkDeviceMemory here
        static VkDeviceMemory vBufferMemory;

        static std::vector<VkBuffer> mBufferList;

        static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


        static void CreateVertexBufferForModel(Model * targetModel);

    };

}

#endif //TANDENENGINE_BUFFERMANAGER_H
