//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsSystem.h"
#include <algorithm>
#include "../../Core/Math/NilsMath.h"

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
    // TODO I assume I can get reference to the objects at the position (to avoid having to access each time), given the above
    void PhysicsSystem::CollisionUpdate(){
        int n = mColliders.size();
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {
                /*
                //AABB Boxes
                if((mColliders[i]->mPosition.x - mSize.x/2) <= (mColliders[j]->mPosition.x + mSize.x/2) && (mColliders[i]->mPosition.x + mSize.x/2) >= (mColliders[j]->mPosition.x - mSize.x/2)) {
                    if((mColliders[i]->mPosition.y - mSize.y/2) <= (mColliders[j]->mPosition.y + mSize.y/2) && (mColliders[i]->mPosition.y + mSize.y/2) >= (mColliders[j]->mPosition.y - mSize.y/2)) {
                        if((mColliders[i]->mPosition.z - mSize.z/2) <= (mColliders[j]->mPosition.z + mSize.z/2) && (mColliders[i]->mPosition.z + mSize.z/2) >= (mColliders[j]->mPosition.z - mSize.z/2)) {
                            # TRIGGERED
                        }
                    }
                }
                // Sphere v Sphere
                //distance should end up being its own function in NilsMath
                float distance = sqrt(pow(mColliders[i]->mPosition.x - mColliders[j]->mPosition.x, 2.0) * pow(mColliders[i]->mPosition.y - mColliders[j]->mPosition.y, 2.0) * pow(mColliders[i]->mPosition.z - mColliders[j]->mPosition.z, 2.0));
                if (distance < (mColliders[i]->mRadius + mColliders[j]->mRadius)) {
                    # TRIGGERED
                }

                // Box v Sphere
                // if box is i
                Vector3 testPoint;
                testPoint.x = max(mColliders[i]->mPosition.x - mSize.x/2, min(mColliders[j]->mPosition.x, mColliders[i]->mPosition.x + mSize.x/2));
                testPoint.y = max(mColliders[i]->mPosition.y - mSize.y/2, min(mColliders[j]->mPosition.y, mColliders[i]->mPosition.y + mSize.y/2));
                testPoint.z = max(mColliders[i]->mPosition.z - mSize.z/2, min(mColliders[j]->mPosition.z, mColliders[i]->mPosition.z + mSize.z/2));

                float distance = sqrt(pow(testPoint.x - mColliders[j]->mPosition.x, 2.0) * pow(testPoint.y - mColliders[j]->mPosition.y, 2.0) * pow(testPoint.z - mColliders[j]->mPosition.z, 2.0));
                if(distance < mColliders[j]->radius) {
                    # TRIGGERED
                }

                // if box is j
                Vector3 testPoint;
                testPoint.x = max(mColliders[j]->mPosition.x - mSize.x/2, min(mColliders[i]->mPosition.x, mColliders[j]->mPosition.x + mSize.x/2));
                testPoint.y = max(mColliders[j]->mPosition.y - mSize.y/2, min(mColliders[i]->mPosition.y, mColliders[j]->mPosition.y + mSize.y/2));
                testPoint.z = max(mColliders[j]->mPosition.z - mSize.z/2, min(mColliders[i]->mPosition.z, mColliders[j]->mPosition.z + mSize.z/2));

                float distance = sqrt(pow(testPoint.x - mColliders[i]->mPosition.x, 2.0) * pow(testPoint.y - mColliders[i]->mPosition.y, 2.0) * pow(testPoint.z - mColliders[i]->mPosition.z, 2.0));
                if(distance < mColliders[i]->radius) {
                    # TRIGGERED
                }

                # not triggered

                */

            }
        }
    }

}