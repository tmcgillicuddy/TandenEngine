//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_SPRITERENDERER_H
#define TANDENENGINE_SPRITERENDERER_H

#include "Renderer.h"

namespace TandenEngine {

    class SpriteRenderer : public Renderer {
    public:
        SpriteRenderer();

        //Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a sprite renderer object

        //Renderer Overrides
        void Draw() override;
    };

}

#endif //TANDENENGINE_SPRITERENDERER_H
