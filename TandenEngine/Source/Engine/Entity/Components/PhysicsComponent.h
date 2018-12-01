//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_PHYSICSCOMPONENT_H
#define TANDENENGINE_PHYSICSCOMPONENT_H

#include "Component.h"

namespace  TandenEngine {

    class PhysicsComponent : public Component {
        friend class PhysicsSystem;
        virtual void PhysicsUpdate() {};
    public:
        void Register() override;

        std::string ToString() override;
    };

}

#endif //TANDENENGINE_PHYSICSCOMPONENT_H
