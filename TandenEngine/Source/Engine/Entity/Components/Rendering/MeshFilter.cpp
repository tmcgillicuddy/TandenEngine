//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "MeshFilter.h"

namespace TandenEngine {

    Component *MeshFilter::ConvertFromString(std::vector<std::string> input) {
        return NULL;
    }

    std::unique_ptr<Component> MeshFilter::Clone() {
        return std::unique_ptr<MeshFilter>(this);
    }
}  // namespace TandenEngine
