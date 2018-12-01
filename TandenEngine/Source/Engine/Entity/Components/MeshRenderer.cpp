//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "MeshRenderer.h"
#include <iostream>

namespace TandenEngine {

    MeshRenderer::MeshRenderer() {

    }

    MeshRenderer::~MeshRenderer() {

    }

    void MeshRenderer::Draw() {
        std::cout << "Drawing Mesh Renderer\n";
    }

    std::string MeshRenderer::ToString() {
        std::string data = "MeshRenderer\n";
        return data;
    }

    std::unique_ptr<Component> MeshRenderer::Clone() {
        return std::unique_ptr<MeshRenderer>(this);
    }

    Component *MeshRenderer::ConvertFromString(std::string input) {
        return NULL;
    }

}