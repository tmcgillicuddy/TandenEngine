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

    BoxCollider::BoxCollider( Vector3 position, Vector3 rotation, Vector3 scale) {
        mType = ComponentType::BOXCOLLIDER;
        mLocalPosition = position, mLocalRotation = rotation, mScale = scale;
        mGlobalPosition = mTransform->position + position;
        mGlobalRotation = mTransform->rotation + rotation;
    }

    BoxCollider::~BoxCollider() {
    }

    void BoxCollider::Update() {
        std::cout << "Updating Box Collider\n";
    }

    std::string BoxCollider::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        return data;
    }

    std::unique_ptr<Component> BoxCollider::Clone() {
        return std::unique_ptr<BoxCollider>(this);
    }

    Component *BoxCollider::ConvertFromString(std::vector<std::string> input) {
        BoxCollider * newComp = new BoxCollider();

        return newComp;
    }
}