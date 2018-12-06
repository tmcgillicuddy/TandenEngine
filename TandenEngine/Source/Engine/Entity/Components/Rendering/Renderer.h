//
// Created by thomas.mcgillicuddy on 10/31/2018.
// Base renderer component

#ifndef HWENGINE_RENDERER_H
#define HWENGINE_RENDERER_H

#include "../Component.h"

namespace TandenEngine {

    class Renderer : public Component {
        friend class RenderingSystem;

        virtual void Draw()=0;

        void Update() {};

        void Register() override;

        std::string ToString() override {return std::string();};
        Component * ConvertFromString(std::vector<std::string>) override { return NULL;}; //Takes in some string data and will output a renderer object
    };

}

#endif //HWENGINE_RENDERER_H
