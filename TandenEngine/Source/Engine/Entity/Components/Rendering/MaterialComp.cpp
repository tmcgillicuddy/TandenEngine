//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "MaterialComp.h"

namespace TandenEngine {

    MaterialComp::MaterialComp() {

    }

    Component *MaterialComp::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }

    std::string MaterialComp::ToString() {
        return Component::ToString();
    }

    std::unique_ptr<Component> MaterialComp::Clone() {
        return std::unique_ptr<Component>();
    }

    void MaterialComp::Update() {
    }
}