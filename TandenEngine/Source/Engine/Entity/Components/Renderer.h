//
// Created by thomas.mcgillicuddy on 10/31/2018.
// Base renderer component

#ifndef HWENGINE_RENDERER_H
#define HWENGINE_RENDERER_H

#include "Component.h"

namespace TandenEngine {

    class Renderer : public Component {
        friend class RenderingSystem;

        virtual void Draw() {};

        void Update() override;

        void Register() override;
    };

}

#endif //HWENGINE_RENDERER_H
