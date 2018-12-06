//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_PHYSICSSYSTEM_H
#define TANDENENGINE_PHYSICSSYSTEM_H

#include <vector>

#include "../Entity/Components/Physics/PhysicsComponent.h"
#include "../Entity/Components/Physics/Collider.h"
#include "../Entity/Components/Physics/BoxCollider.h"

namespace TandenEngine {

    class PhysicsSystem {
        static std::vector<PhysicsComponent *> mPhysicsObjects;
        static std::vector<Collider *> mColliders;

    public:
        static void PhysicsUpdate();

        static void CollisionUpdate();

        static void RegisterPhysicsObject(PhysicsComponent * newObject);
        static void RegisterColliderObject(Collider * newObject);
    };

}

#endif //TANDENENGINE_PHYSICSSYSTEM_H
