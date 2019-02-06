//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "RigidBody.h"
#include "../Transform.h"
#include "../../../../Core/Timer/Timer.h"

namespace TandenEngine {

    RigidBody::RigidBody() {
    }

    void RigidBody::Update() {
        mTransform->mTransformData.r1.x = sin(Timer::mCurrentTime) * 10;
        // std::cout<<mTransform->position;
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
