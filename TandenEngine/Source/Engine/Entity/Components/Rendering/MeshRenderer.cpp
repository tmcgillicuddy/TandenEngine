//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include <iostream>
#include "../../../../Core/Debugger/Debug.h"
#include "MeshRenderer.h"

namespace TandenEngine {

    MeshRenderer::MeshRenderer() {
        mType = ComponentType::MESHRENDERER;
    }

    MeshRenderer::~MeshRenderer() {
    }

    void MeshRenderer::Draw() {
        // std::cout << "Drawing Mesh Renderer\n";
        for (const auto &vertices : mpMesh->mModelResource->mVertices) {
            std::cout << vertices.mPos << std::endl << vertices.mColor << std::endl;
        }
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
