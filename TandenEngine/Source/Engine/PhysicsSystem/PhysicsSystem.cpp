//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsSystem.h"
#include <algorithm>
#include "NilsMath.h"

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
    void PhysicsSystem::CollisionUpdate(){

        // Updating Global Transforms in every collider
        // In theory, this should only be happening to GameObjects that are actually moving
        int n = mColliders.size();
        for(auto col : mColliders) {
            col->mGlobalPosition = col->mTransform->position + col->mLocalPosition;
            col->mGlobalRotation = col->mTransform->rotation + col->mLocalRotation;
        }

        Collider *colA, *colB;

        // cycle through the whole thing, and then everything after the start point, to avoid checking the same pair twice
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j) {

                colA = mColliders[i];
                colB = mColliders[j];

                if(colA->mType == BOXCOLLIDER && colB->mType == BOXCOLLIDER) {
                    if((colA->mGlobalPosition.x - colA->mScale.x/2) <= (colB->mGlobalPosition.x + colB->mScale.x/2) && (colA->mGlobalPosition.x + colA->mScale.x/2) >= (colB->mGlobalPosition.x - colB->mScale.x/2)) {
                        if((colA->mGlobalPosition.y - colA->mScale.y/2) <= (colB->mGlobalPosition.y + colB->mScale.y/2) && (colA->mGlobalPosition.y + colA->mScale.y/2) >= (colB->mGlobalPosition.y - colB->mScale.y/2)) {
                            if((colA->mGlobalPosition.z - colA->mScale.z/2) <= (colB->mGlobalPosition.z + colB->mScale.z/2) && (colA->mGlobalPosition.z + colA->mScale.z/2) >= (colB->mGlobalPosition.z - colB->mScale.z/2)) {
                                std::cout << "YES Collision between " << i << " and " << j << std::endl;
                                continue;
                            }
                        }
                    }
                }
                else if((colA->mType == SPHERECOLLIDER && colB->mType == SPHERECOLLIDER)) {
                    float distance;
                    distance = static_cast<float>(sqrt(pow(colA->mGlobalPosition.x - colB->mGlobalPosition.x, 2.0) * pow(colA->mGlobalPosition.y - colB->mGlobalPosition.y, 2.0) * pow(colA->mGlobalPosition.z - colB->mGlobalPosition.z, 2.0)));
                    if (distance < (colA->mScale.x + colB->mScale.x)) {
                        std::cout << "YES Collision between " << i << " and " << j << std::endl;
                        continue;
                    }
                }
                else if((colA->mType == BOXCOLLIDER && colB->mType == SPHERECOLLIDER)) {
                    Vector3 testPoint;
                    testPoint.x = fmax(colA->mGlobalPosition.x - colA->mScale.x/2, fmin(colB->mGlobalPosition.x, colA->mGlobalPosition.x + colA->mScale.x/2));
                    testPoint.y = fmax(colA->mGlobalPosition.y - colA->mScale.y/2, fmin(colB->mGlobalPosition.y, colA->mGlobalPosition.y + colA->mScale.y/2));
                    testPoint.z = fmax(colA->mGlobalPosition.z - colA->mScale.z/2, fmin(colB->mGlobalPosition.z, colA->mGlobalPosition.z + colA->mScale.z/2));

                    float distance;
                    distance = static_cast<float>(sqrt(pow(testPoint.x - colB->mGlobalPosition.x, 2.0) * pow(testPoint.y - colB->mGlobalPosition.y, 2.0) * pow(testPoint.z - colB->mGlobalPosition.z, 2.0)));
                    if(distance < colB->mScale.x) {
                        std::cout << "YES Collision between " << i << " and " << j << std::endl;
                        continue;
                    }
                }
                else if((colA->mType == SPHERECOLLIDER && colB->mType == BOXCOLLIDER)) {
                    Vector3 testPoint;
                    testPoint.x = fmax(colB->mGlobalPosition.x - colB->mScale.x/2, fmin(colA->mGlobalPosition.x, colB->mGlobalPosition.x + colB->mScale.x/2));
                    testPoint.y = fmax(colB->mGlobalPosition.y - colB->mScale.y/2, fmin(colA->mGlobalPosition.y, colB->mGlobalPosition.y + colB->mScale.y/2));
                    testPoint.z = fmax(colB->mGlobalPosition.z - colB->mScale.z/2, fmin(colA->mGlobalPosition.z, colB->mGlobalPosition.z + colB->mScale.z/2));

                    float distance;
                    distance = static_cast<float>(sqrt(pow(testPoint.x - colA->mGlobalPosition.x, 2.0) * pow(testPoint.y - colA->mGlobalPosition.y, 2.0) * pow(testPoint.z - colA->mGlobalPosition.z, 2.0)));
                    if(distance < colA->mScale.x) {
                        std::cout << "YES Collision between " << i << " and " << j << std::endl;
                        continue;
                    }
                }

                std::cout << "No Collision between " << i << " and " << j << std::endl;
            }
        }
    }

}