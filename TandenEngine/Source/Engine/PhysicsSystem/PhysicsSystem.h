//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_PHYSICSSYSTEM_H
#define TANDENENGINE_PHYSICSSYSTEM_H

#include <vector>

#include "../Entity/Components/PhysicsComponent.h"

namespace TandenEngine {

    class PhysicsSystem {
        static std::vector<PhysicsComponent *> mPhysicsObjects;

    public:
        static void PhysicsUpdate();

        static void RegisterPhysicsObject(PhysicsComponent * newObject);
    };

}

#endif //TANDENENGINE_PHYSICSSYSTEM_H
