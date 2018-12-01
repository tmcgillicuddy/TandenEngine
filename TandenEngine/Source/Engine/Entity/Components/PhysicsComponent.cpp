//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsComponent.h"
#include "../../PhysicsSystem/PhysicsSystem.h"

namespace  TandenEngine {

    void PhysicsComponent::Register() {
        PhysicsSystem::RegisterPhysicsObject(this);
    }

    std::string PhysicsComponent::ToString() {
        std::string data = "PhysicsComponent\n";
        return data;
    }

    Component *PhysicsComponent::ConvertFromString(std::string input) {
        return NULL;
    }
}