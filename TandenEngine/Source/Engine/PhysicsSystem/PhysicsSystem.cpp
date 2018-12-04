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


    // https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
    // TODO how do i get the variables specifically in boxColliders?
    void PhysicsSystem::CollisionUpdate(){
        int n = mColliders.size();
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                /*
                if(mColliders[i]->minX <= mColliders[j]->maxX && mColliders[i]->maxX >= mColliders[j]->minX) {
                    if(mColliders[i]->minY <= mColliders[j]->maxY && mColliders[i]->maxY >= mColliders[j]->minY) {
                        if(mColliders[i]->minY <= mColliders[j]->maxY && mColliders[i]->maxY >= mColliders[j]->minY) {
                            # TRIGGERED
                        }
                    }
                }
                */
                // # not triggered
            }
        }
    }

}