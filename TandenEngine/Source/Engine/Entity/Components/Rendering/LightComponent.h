//
// Created by thomas.mcgillicuddy on 12/4/2018.
//

#ifndef TANDENENGINE_LIGHTCOMPONENT_H
#define TANDENENGINE_LIGHTCOMPONENT_H

#include "../Component.h"
#include "../../../RenderingSystem/LightBehaviors/LightBehavior.h"

namespace TandenEngine {
    class LightComponent : public Component {
    public:
        LightBehavior * mLightBehavior; //How this light is supposed to behave

        //Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a mesh collider object
        void Register() override; //Register light with rendering system
    };

}

#endif //TANDENENGINE_LIGHTCOMPONENT_H
