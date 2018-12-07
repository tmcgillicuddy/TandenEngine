//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "RigidBody.h"

namespace TandenEngine {

    RigidBody::RigidBody() {
    }

    void RigidBody::Update() {
    }

    std::unique_ptr<Component> RigidBody::Clone() {
        return std::unique_ptr<RigidBody>(this);
    }

    std::string RigidBody::ToString() {
        return PhysicsComponent::ToString();
    }

    Component *RigidBody::ConvertFromString(std::vector<std::string> input) {
        return PhysicsComponent::ConvertFromString(input);
    }
}