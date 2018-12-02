//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_SPRITERENDERER_H
#define HWENGINE_SPRITERENDERER_H

#include "Renderer.h"

namespace TandenEngine {

    class SpriteRenderer : public Renderer {
        void Draw() override;

        std::string ToString();
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a sprite renderer object
    };

}

#endif //HWENGINE_SPRITERENDERER_H
