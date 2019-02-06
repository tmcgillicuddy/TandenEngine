//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_RIGIDBODY_H
#define TANDENENGINE_RIGIDBODY_H

#include "PhysicsComponent.h"
#include "../../../../Core/Math/NilsMath.h"

namespace TandenEngine {

    class RigidBody : public PhysicsComponent{
     public:
        RigidBody (const float &mass = 1.0f, const float &friction = 0.0f );
        ~RigidBody() {}

        float mMass;
        float mFriction;
        vec3 mLinearVelocity;
        vec3 mAngularVelocity;
        vec3 mCenterOfMass;

        void UpdateGravity();

        // Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a mesh collider object
        Component * ConvertFromString(std::vector<std::string> input) override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_RIGIDBODY_H
