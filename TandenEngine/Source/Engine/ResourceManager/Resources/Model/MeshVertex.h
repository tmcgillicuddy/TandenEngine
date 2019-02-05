//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHVERTEX_H
#define HWENGINE_MESHVERTEX_H

#include "NilsMath.h"
#include "../../../RenderingSystem/VulkanInfo.h"
#include <array>

namespace TandenEngine {

    class MeshVertex {
     public:
        MeshVertex(Vector3 newPos, Vector3 newColor) {mPos = newPos; mColor = newColor;};

        static VkVertexInputBindingDescription GetBindingDescription() {

            VkVertexInputBindingDescription bindingDescription = {};

            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(MeshVertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions() {

            std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(MeshVertex, mPos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(MeshVertex, mColor);

            return attributeDescriptions;
        }


     public: //PRIVATE
        Vector3 mPos;
        Vector3 mColor;
        Vector2 mUV;
        Vector3 mNormal;
        Vector3 mTangent;
    };
}  // namespace TandenEngine

namespace std {
    template<> struct ::std::hash<TandenEngine::MeshVertex> {
        size_t operator()(TandenEngine::MeshVertex const& vertex) const {
            return ((::std::hash<TandenEngine::vec3>()(vertex.mPos  ) ^
                     (::std::hash<TandenEngine::vec3>()(vertex.mColor) << 1)) >> 1) ^
                   (::std::hash<TandenEngine::vec2>()(vertex.mUV) << 1);
        }
    };
}

#endif  // HWENGINE_MESHVERTEX_H
