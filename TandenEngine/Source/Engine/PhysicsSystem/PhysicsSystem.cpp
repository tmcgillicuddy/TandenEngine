//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsSystem.h"

namespace TandenEngine {

    std::vector<PhysicsComponent*> PhysicsSystem::mPhysicsObjects;
    std::vector<Collider*> PhysicsSystem::mColliders;

    void PhysicsSystem::PhysicsUpdate() {

        CollisionUpdate();

        for (const auto &physicsObj : mPhysicsObjects) {
            physicsObj->PhysicsUpdate();
        }
    }

    void PhysicsSystem::RegisterPhysicsObject(PhysicsComponent *newObject) {
        mPhysicsObjects.emplace_back(newObject);
    }

    void PhysicsSystem::RegisterColliderObject(Collider *newObject) {
        mColliders.emplace_back(newObject);
    }

    void PhysicsSystem::CollisionUpdate(){
        // TODO how2checkPhysx
    }

}