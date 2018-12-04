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
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        return data;
    }

    Component *PhysicsComponent::ConvertFromString(std::vector<std::string>) {
        return NULL;
    }
}