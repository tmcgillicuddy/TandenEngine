//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include <iostream>
#include "../../../../Core/Debugger/Debug.h"
#include "MeshRenderer.h"

namespace TandenEngine {

    MeshRenderer::MeshRenderer() {
        mType = ComponentType::MESHRENDERER;

        // Prepare uniform buffer
        // TODO(Rosser) create uniform buffer (size of mvpubo)
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
