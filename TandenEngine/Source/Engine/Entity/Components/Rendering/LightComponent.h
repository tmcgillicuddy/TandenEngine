//
// Created by thomas.mcgillicuddy on 12/4/2018.
//

#ifndef TANDENENGINE_LIGHTCOMPONENT_H
#define TANDENENGINE_LIGHTCOMPONENT_H

#include "../Component.h"

namespace TandenEngine {
    class LightComponent : public Component {
    public:
        void Update() override;

        void Register() override; //Register light with rendering system
    };

}

#endif //TANDENENGINE_LIGHTCOMPONENT_H
