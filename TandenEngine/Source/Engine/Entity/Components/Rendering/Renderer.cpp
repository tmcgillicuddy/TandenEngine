//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include <iostream>

#include "Renderer.h"
#include "../../../RenderingSystem/RenderingSystem.h"


namespace TandenEngine {

    void Renderer::Register() {
        RenderingSystem::RegisterRenderer(this);
    }

}  // namespace TandenEngine
