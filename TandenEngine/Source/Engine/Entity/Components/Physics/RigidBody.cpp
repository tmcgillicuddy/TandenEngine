//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "RigidBody.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"
#include "../Transform.h"
#include "../../../../Core/Timer/Timer.h"
#include "Debug.h"

namespace TandenEngine {

    RigidBody::RigidBody(const float &mass, const float &friction) {
        mMass = mass;
        mFriction = friction;
        mCenterOfMass = vec3::ZERO;
        mAccelerationLinear.y = -mGravity;
    }

    void RigidBody::PhysicsUpdate() {
        // update transforms based on velocity
        if (!mStatic) {
            mTransform->mTransformLocal.r1.x += mVelocityLinear.x;
            mTransform->mTransformLocal.r1.y += mVelocityLinear.y;
            mTransform->mTransformLocal.r1.z += mVelocityLinear.z;

            mTransform->mTransformLocal.r2.x += mVelocityAngular.x;
            mTransform->mTransformLocal.r2.y += mVelocityAngular.y;
            mTransform->mTransformLocal.r2.z += mVelocityAngular.z;
        }

        // update velocities based on accelerations and drag force acting against it
        mVelocityLinear.x += mAccelerationLinear.x + mDragForce.x;
        mVelocityLinear.y += mAccelerationLinear.y + mDragForce.y;
        mVelocityLinear.z += mAccelerationLinear.z + mDragForce.z;

        mVelocityAngular.x += mAccelerationAngular.x + mDragForce.x;
        mVelocityAngular.y += mAccelerationAngular.y + mDragForce.y;
        mVelocityAngular.z += mAccelerationAngular.z + mDragForce.z;
        // Debug::Log("%v3", mLinearVelocity);

        // reset forces, because they're only applied for a frame
        mAccelerationLinear -= mForceLinear * (1.0f / mMass);
        mAccelerationLinear -= mForceAngular * (1.0f / mMass);
        mForceLinear = vec3(0.0, 0.0, 0.0);
        mForceAngular = vec3(0.0, 0.0, 0.0);
    }

    // Changes gravity to given amount, and updates acceleration accordingly
    void RigidBody::SetGravity(const float& gravity) {
        mAccelerationLinear.y += mGravity;
        mGravity = gravity;
        mAccelerationLinear.y -= mGravity;
    }

    // Add force for a single update
    void RigidBody::AddForceLinear(const vec3& toAdd) {
        mForceLinear = toAdd;
        mAccelerationLinear += mForceLinear * (1.0f / mMass);
    }

    void RigidBody::AddForceAngular(const vec3& toAdd) {
        mForceAngular = toAdd;
        mAccelerationAngular += mForceAngular * (1.0f / mMass);
    }

    // Returns the calculated drag, in case you need it for anything
    vec3 RigidBody::SetDragForce(const float &dragConst) {
        // Should generally be called if a RB enters a new environment
        // This is a basic version that doesn't account for all factors
        // Force = Speed of object * the constant, in the inverse direction of velocity
        mDragForce = mVelocityLinear * this->GetSpeed() * dragConst * -1.0;
        return mDragForce;
    }

    float RigidBody::GetSpeed() {
        return mVelocityLinear.Magnitude();
    }

    std::unique_ptr<Component> RigidBody::Clone() {
        return std::unique_ptr<RigidBody>(this);
    }

    std::string RigidBody::ToString() {
        std::string data = Component::ToString();  // Call the base to string function
        return data;
    }

    Component *RigidBody::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}  // namespace TandenEngine
