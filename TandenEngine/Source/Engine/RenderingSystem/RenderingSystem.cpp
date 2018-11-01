//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "RenderingSystem.h"

namespace TandenEngine {

    std::vector<Renderer *> RenderingSystem::mRenderers;

    void RenderingSystem::Draw() {
        for (const auto &rend : mRenderers) {
            rend->Draw();
        }
    }

    void RenderingSystem::RegisterRenderer(Renderer *newRenderer) {
        mRenderers.emplace_back(newRenderer);
    }

}