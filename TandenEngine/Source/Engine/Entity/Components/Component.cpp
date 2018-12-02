//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Component.h"

namespace TandenEngine {

    std::string Component::ToString() {
        std::string data = std::to_string(static_cast<int>(mType)) +'\n';
        return data;
    }
}