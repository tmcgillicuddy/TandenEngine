//
// Created by nils.steinbuegl on 12/4/2018.
//

#include "SphereCollider.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"


namespace  TandenEngine {

    SphereCollider::SphereCollider() {
        mType = ComponentType::SPHERECOLLIDER;
    }

    SphereCollider::~SphereCollider() {
    }

    void SphereCollider::Update() {
        std::cout << "Updating Sphere Collider\n";
    }

    std::unique_ptr<Component> SphereCollider::Clone() {
        return std::unique_ptr<SphereCollider>(this);
    }

    std::string SphereCollider::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        return data;
    }

    Component *SphereCollider::ConvertFromString(std::vector<std::string>) {
        return NULL;
    }
}