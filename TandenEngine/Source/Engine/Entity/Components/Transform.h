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

        Transform();

        ~Transform();

        void Update() override;

        std::string ToString() override;
    };

}

#endif //HWENGINE_TRANSFORM_H
