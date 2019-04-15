//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "PhysicsSystem.h"
#include <algorithm>
#include "NilsMath.h"
#include "../Entity/GameObject.h"
#include <cmath>

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
    void PhysicsSystem::CollisionUpdate() {
        // Updating Global Transforms in every collider
        // In theory, this should only be happening to GameObjects that are actually moving
        int n = mColliders.size();
        for (auto col : mColliders) {
            col->mGlobalPosition = col->mTransform->mTransformGlobal.r1 + col->mLocalPosition;
            col->mGlobalRotation = col->mTransform->mTransformGlobal.r2 + col->mLocalRotation;
        }

        Collider *colA, *colB;

        // cycle through the whole thing, and then everything after the start point,
        // to avoid checking the same pair twice
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                colA = mColliders[i];
                colB = mColliders[j];


                if (colA->mType == BOXCOLLIDER && colB->mType == BOXCOLLIDER) {
                    BoxBoxCollision(colA, colB);
                } else if ((colA->mType == SPHERECOLLIDER && colB->mType == SPHERECOLLIDER)) {
                    SphereSphereCollision(colA, colB);
                } else if ((colA->mType == BOXCOLLIDER && colB->mType == SPHERECOLLIDER) ||
                        (colA->mType == SPHERECOLLIDER && colB->mType == BOXCOLLIDER)) {
                    BoxSphereCollision(colA, colB);
                } else if (colA->mType == MESHCOLLIDER && colB->mType == MESHCOLLIDER) {
                    MeshMeshCollision(colA, colB);
                } else if ((colA->mType == MESHCOLLIDER && colB->mType == SPHERECOLLIDER) ||
                        (colA->mType == SPHERECOLLIDER && colB->mType == MESHCOLLIDER)) {
                    MeshSphereCollision(colA, colB);
                } else if ((colA->mType == BOXCOLLIDER && colB->mType == MESHCOLLIDER) ||
                        (colA->mType == MESHCOLLIDER && colB->mType == BOXCOLLIDER)) {
                    MeshBoxCollision(colA, colB);
                }
            }
        }
    }


    void PhysicsSystem::BoxBoxCollision(Collider * colA, Collider * colB) {
        if ((colA->mGlobalPosition.x - colA->mScale.x/2) <=
        (colB->mGlobalPosition.x + colB->mScale.x/2) &&
        (colA->mGlobalPosition.x + colA->mScale.x/2) >=
        (colB->mGlobalPosition.x - colB->mScale.x/2)) {
            if ((colA->mGlobalPosition.y - colA->mScale.y/2) <=
            (colB->mGlobalPosition.y + colB->mScale.y/2) &&
            (colA->mGlobalPosition.y + colA->mScale.y/2) >=
            (colB->mGlobalPosition.y - colB->mScale.y/2)) {
                if ((colA->mGlobalPosition.z - colA->mScale.z/2) <=
                (colB->mGlobalPosition.z + colB->mScale.z/2) &&
                (colA->mGlobalPosition.z + colA->mScale.z/2) >=
                (colB->mGlobalPosition.z - colB->mScale.z/2)) {
                    std::cout << "Box v Box Collision between " <<
                        colA->mParentObject->GetName() << " and " <<
                        colB->mParentObject->GetName() << std::endl;
                }
            }
        }
    }
    void PhysicsSystem::SphereSphereCollision(Collider * colA, Collider * colB) {
        float distance;
        distance = NilsMath::Dist(colA->mGlobalPosition, colB->mGlobalPosition);
        if (distance < (colA->mScale.x + colB->mScale.x)) {
            std::cout << "Sphere v Sphere Collision between " <<
                colA->mParentObject->GetName() << " and " <<
                colB->mParentObject->GetName() << std::endl;
        }
    }
    void PhysicsSystem::BoxSphereCollision(Collider * colA, Collider * colB) {
        if ((colA->mType == BOXCOLLIDER && colB->mType == SPHERECOLLIDER)) {
            vec3 testPoint;
            testPoint.x = fmax(colA->mGlobalPosition.x - colA->mScale.x / 2,
                    fmin(colB->mGlobalPosition.x, colA->mGlobalPosition.x + colA->mScale.x / 2));
            testPoint.y = fmax(colA->mGlobalPosition.y - colA->mScale.y / 2,
                    fmin(colB->mGlobalPosition.y, colA->mGlobalPosition.y + colA->mScale.y / 2));
            testPoint.z = fmax(colA->mGlobalPosition.z - colA->mScale.z / 2,
                    fmin(colB->mGlobalPosition.z, colA->mGlobalPosition.z + colA->mScale.z / 2));

            float distance;
            distance = NilsMath::Dist(testPoint, colB->mGlobalPosition);
            if (distance < colB->mScale.x) {
                std::cout << "Box v Sphere Collision between "
                        << colA->mParentObject->GetName() << " and "
                        << colB->mParentObject->GetName() << std::endl;
            }
        } else if ((colA->mType == SPHERECOLLIDER && colB->mType == BOXCOLLIDER)) {
            vec3 testPoint;
            testPoint.x = fmax(colB->mGlobalPosition.x - colB->mScale.x / 2,
                    fmin(colA->mGlobalPosition.x, colB->mGlobalPosition.x + colB->mScale.x / 2));
            testPoint.y = fmax(colB->mGlobalPosition.y - colB->mScale.y / 2,
                    fmin(colA->mGlobalPosition.y, colB->mGlobalPosition.y + colB->mScale.y / 2));
            testPoint.z = fmax(colB->mGlobalPosition.z - colB->mScale.z / 2,
                    fmin(colA->mGlobalPosition.z, colB->mGlobalPosition.z + colB->mScale.z / 2));

            float distance;
            distance = NilsMath::Dist(colA->mGlobalPosition, testPoint);
            if (distance < colA->mScale.x) {
                std::cout << "Sphere v Box Collision between "
                        << colA->mParentObject->GetName() << " and "
                        << colB->mParentObject->GetName() << std::endl;
            }
        }
    }
    void PhysicsSystem::MeshMeshCollision(Collider * colA, Collider * colB) {
        // Do the collision tests
    }
    void PhysicsSystem::MeshSphereCollision(Collider * colA, Collider * colB) {
        // Do the collision tests
    }
    void PhysicsSystem::MeshBoxCollision(Collider * colA, Collider * colB) {
        // Do the collision tests
    }
}  // namespace TandenEngine
