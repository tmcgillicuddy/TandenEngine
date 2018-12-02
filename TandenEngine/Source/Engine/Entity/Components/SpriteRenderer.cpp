//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "SpriteRenderer.h"

namespace TandenEngine {

    void SpriteRenderer::Draw() {

    }

    std::string SpriteRenderer::ToString() {
        std::string data = "SpriteRenderer\n";
        return data;
    }

    Component *SpriteRenderer::ConvertFromString(std::vector<std::string> input) {
        return NULL;
    }

}