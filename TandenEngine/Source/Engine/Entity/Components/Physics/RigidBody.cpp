//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "RigidBody.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"
#include "../Transform.h"
#include "../../../../Core/Timer/Timer.h"

namespace TandenEngine {

    RigidBody::RigidBody(const float &mass, const float &friction) {
        mMass = mass;
        mFriction = friction;
        mCenterOfMass = mTransform->mTransformData.r1;  // default to center of object
        mLinearAcceleration.y = -mGravity;
    }

    void RigidBody::PhysicsUpdate() {
        // mTransform->mTransformData.r1.x = sin(Timer::mCurrentTime) * 10;

        // update transforms based on velocity
        if(!mStatic)
        {
            mTransform->mTransformData.r1.x += mLinearVelocity.x;
            mTransform->mTransformData.r1.y += mLinearVelocity.y;
            mTransform->mTransformData.r1.z += mLinearVelocity.z;

            mTransform->mTransformData.r2.x += mAngularVelocity.x;
            mTransform->mTransformData.r2.y += mAngularVelocity.y;
            mTransform->mTransformData.r2.z += mAngularVelocity.z;
        }

        // update velocities based on accelerations
        mLinearVelocity.x += mLinearAcceleration.x;
        mLinearVelocity.y += mLinearAcceleration.y;
        mLinearVelocity.z += mLinearAcceleration.z;

        mAngularVelocity.x += mAngularAcceleration.x;
        mAngularVelocity.y += mAngularAcceleration.y;
        mAngularVelocity.z += mAngularAcceleration.z;
    }

    void RigidBody::SetGravity(const float gravity) {
        // apply gravity based on time (@9.8m/s)
        //mTransform->mTransformData.r1.x = sin(Timer::mCurrentTime) * 10;
        // std::cout<<mTransform->position;
        mLinearAcceleration.y += mGravity;
        mGravity = gravity;
        mLinearAcceleration.y -= mGravity;
    }

    float RigidBody::GetSpeed() {
        return mLinearVelocity.Norm();
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
