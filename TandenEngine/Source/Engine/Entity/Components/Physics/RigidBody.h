//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_RIGIDBODY_H
#define TANDENENGINE_RIGIDBODY_H

#include "PhysicsComponent.h"
#include "../../../../Core/Math/NilsMath.h"

namespace TandenEngine {

    class RigidBody : public PhysicsComponent{
     float mGravity = 9.8f;
     vec3 mForceLinear;
     vec3 mForceAngular;

     public:
        RigidBody(const float &mass = 1.0f, const float &friction = 0.0f);
        ~RigidBody() {}

        bool mStatic = false;
        float mMass;
        float mFriction;
        vec3 mVelocityLinear;
        vec3 mAccelerationLinear;
        vec3 mVelocityAngular;
        vec3 mAccelerationAngular;
        vec3 mCenterOfMass;
        vec3 mDragForce;

        void SetGravity(const float& gravity);
        vec3 SetDragForce(const float& dragConst);
        void AddForceLinear(const vec3& toAdd);
        void AddForceAngular(const vec3& toAdd);

        float GetSpeed();

        // Component Overrides
        void Update() override {};
        void PhysicsUpdate() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a mesh collider object
        Component * ConvertFromString(std::vector<std::string> input) override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_RIGIDBODY_H
