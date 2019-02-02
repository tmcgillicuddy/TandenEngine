//
// Created by nils.steinbuegl on 12/3/2018.
//

#include "BoxCollider.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"


namespace  TandenEngine {

    BoxCollider::BoxCollider() {
        std::cout << "Making Box Collider\n";
        mType = ComponentType::BOXCOLLIDER;
    }

    BoxCollider::BoxCollider( vec3 position, vec3 rotation, vec3 scale) {
        mType = ComponentType::BOXCOLLIDER;
        mLocalPosition = position, mLocalRotation = rotation, mScale = scale;
        mGlobalPosition = mTransform->mTransformData.r1 + position;
        mGlobalRotation = mTransform->mTransformData.r2 + rotation;
    }

    BoxCollider::~BoxCollider() {
    }

    void BoxCollider::Update() {
        //std::cout << "Updating Box Collider\n";
    }

    std::string BoxCollider::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        return data;
    }

    Component *BoxCollider::ConvertFromString(std::vector<std::string>) {
        return NULL;
    }

    std::unique_ptr<Component> BoxCollider::Clone() {
        return std::unique_ptr<BoxCollider>(this);
    }
}