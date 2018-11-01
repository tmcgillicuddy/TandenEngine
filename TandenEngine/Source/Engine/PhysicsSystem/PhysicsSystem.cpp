//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsSystem.h"

namespace TandenEngine {

    std::vector<PhysicsComponent*> PhysicsSystem::mPhysicsObjects;

    void PhysicsSystem::PhysicsUpdate() {
        for (const auto &physicsObj : mPhysicsObjects) {
            physicsObj->PhysicsUpdate();
        }
    }

    void PhysicsSystem::RegisterPhysicsObject(PhysicsComponent *newObject) {
        mPhysicsObjects.emplace_back(newObject);
    }

}