//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Component.h"
#include "../GameObject.h"
#include "Transform.h"
#include <iostream>

namespace TandenEngine {

    std::string Component::ToString() {
        std::string data = std::to_string(static_cast<int>(mType)) +'\n';
        return data;
    }

    void Component::SetBaseComponent(GameObject *gameObj) {
        mParentObject = gameObj;
        mTransform = dynamic_cast<Transform*>(mParentObject->GetComponent<Transform>());
    }
}