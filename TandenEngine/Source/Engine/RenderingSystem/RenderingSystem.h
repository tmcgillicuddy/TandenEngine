//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_RENDERINGSYSTEM_H
#define HWENGINE_RENDERINGSYSTEM_H

#include <vector>

#include "../Entity/Components/Renderer.h"

namespace TandenEngine {

    class RenderingSystem {

        static std::vector<Renderer *> mRenderers;

    public:
        static void Draw();

        static void RegisterRenderer(Renderer *newRenderer);
    };

}

#endif //HWENGINE_RENDERINGSYSTEM_H
