//
// Created by thomas.mcgillicuddy on 10/31/2018.
// Base renderer component

#ifndef TANDENENGINE_RENDERER_H
#define TANDENENGINE_RENDERER_H

#include "../Component.h"

namespace TandenEngine {

    class Renderer : public Component {
        friend class RenderingSystem;

        void Update() override {};

        void Register() override;

        std::string ToString() override {return std::string();};

        // Takes in some string data and will output a renderer object
        Component * ConvertFromString(std::vector<std::string>) override { return NULL;}
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_RENDERER_H
