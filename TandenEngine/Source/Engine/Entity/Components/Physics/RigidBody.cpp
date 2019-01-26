//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "RigidBody.h"
#include "../Transform.h"
#include "../../../../Core/Timer/Timer.h"

namespace TandenEngine {

    RigidBody::RigidBody(const float &mass, const float &friction) {
        mMass = mass;
        mFriction = friction;
    }

    void RigidBody::Update() {
        UpdateGravity();
        mTransform->position.x += mLinearVelocity.x;
        mTransform->position.x += mLinearVelocity.y;
        mTransform->position.x += mLinearVelocity.z;
    }

    void RigidBody::UpdateGravity() {
        // apply gravity based on time (@9.8m/s)
    }

    std::unique_ptr<Component> RigidBody::Clone() {
        return std::unique_ptr<RigidBody>(this);
    }

    std::string RigidBody::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        return data;
    }

    Component *RigidBody::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}