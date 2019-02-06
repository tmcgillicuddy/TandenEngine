//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsComponent.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"

namespace  TandenEngine {

    void PhysicsComponent::Register() {
        PhysicsSystem::RegisterPhysicsObject(this);
    }
}  // namespace TandenEngine
