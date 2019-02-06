//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_RIGIDBODY_H
#define TANDENENGINE_RIGIDBODY_H

#include "PhysicsComponent.h"

namespace TandenEngine {

    class RigidBody : public PhysicsComponent{
     public:
        RigidBody();

        // Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a mesh collider object
        Component * ConvertFromString(std::vector<std::string> input) override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_RIGIDBODY_H
