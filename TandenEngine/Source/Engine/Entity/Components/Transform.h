//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef TANDENENGINE_TRANSFORM_H
#define TANDENENGINE_TRANSFORM_H

#include <iostream>

#include "Component.h"
#include "NilsMath.h"

namespace TandenEngine {

    class Transform : public Component {
    public:
        // TODO Get consistent naming conventions for these
        Vector3 position;
        Vector3 rotation;
        Vector3 scale = Vector3(1.0, 1.0, 1.0);

        Transform();

        ~Transform();

        void Translate(Vector3 dir);

        void Update() override;

        std::string ToString() override;

        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a transform object

        std::unique_ptr<Component> Clone() override;
    };
}

#endif //TANDENENGINE_TRANSFORM_H
