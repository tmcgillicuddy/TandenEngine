//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include <iostream>
#include "Debug.h"
#include "../../../ResourceManager/BufferManager/BufferManager.h"
#include "MeshRenderer.h"
#include "../../../RenderingSystem/RenderingSystem.h"

namespace TandenEngine {

    MeshRenderer::MeshRenderer() {
        mType = ComponentType::MESHRENDERER;

        // Prepare uniform buffer
        Debug::CheckVKResult(BufferManager::CreateBuffer(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                &mUniformBuffer,
                sizeof(mvpubo)));
        mUniformBuffer.map();
    }

    MeshRenderer::~MeshRenderer() {
    }

    std::string MeshRenderer::ToString() {
        std::string data = Component::ToString();  // Call the base to string function
        // Add component specific attributes
        return data;
    }

    std::unique_ptr<Component> MeshRenderer::Clone() {
        return std::unique_ptr<MeshRenderer>(this);
    }

    Component *MeshRenderer::ConvertFromString(std::vector<std::string> input) {
        MeshRenderer * newComp = new MeshRenderer();

        return newComp;
    }

}  // namespace TandenEngine
