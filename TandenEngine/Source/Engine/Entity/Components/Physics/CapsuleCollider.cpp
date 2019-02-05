//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "CapsuleCollider.h"

namespace TandenEngine {
    CapsuleCollider::CapsuleCollider() {
    }

    void CapsuleCollider::Update() {
    }

    std::unique_ptr<Component> CapsuleCollider::Clone() {
        return std::unique_ptr<Component>();
    }

    std::string CapsuleCollider::ToString() {
        return "";
    }

    Component *CapsuleCollider::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}  // namespace TandenEngine
