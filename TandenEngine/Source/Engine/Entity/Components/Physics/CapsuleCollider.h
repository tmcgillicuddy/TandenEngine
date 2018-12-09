//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_CAPSULECOLLIDER_H
#define TANDENENGINE_CAPSULECOLLIDER_H

#include "Collider.h"

namespace TandenEngine {

    class CapsuleCollider : public Collider {
    public:
        CapsuleCollider();

        //Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a sprite renderer object
    };
}
#endif //TANDENENGINE_CAPSULECOLLIDER_H
