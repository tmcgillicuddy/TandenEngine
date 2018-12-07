//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "MeshCollider.h"

namespace TandenEngine
{
    MeshCollider::MeshCollider() {
    }

    void MeshCollider::Update() {
    }

    std::unique_ptr<Component> MeshCollider::Clone() {
        return std::unique_ptr<MeshCollider>(this);
    }

    std::string MeshCollider::ToString() {
        return "";
    }

    Component *MeshCollider::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}