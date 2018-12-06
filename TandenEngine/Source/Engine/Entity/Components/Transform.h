//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_TRANSFORM_H
#define HWENGINE_TRANSFORM_H

#include <iostream>

#include "Component.h"
#include "../../../Core/Math/Vector3.h"

namespace TandenEngine {

    class Transform : public Component {
    public:
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Transform();

        ~Transform();

        void Update() override;

        std::string ToString() override;

        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a transform object

        std::unique_ptr<Component> Clone() override;
    };
}

#endif //HWENGINE_TRANSFORM_H
