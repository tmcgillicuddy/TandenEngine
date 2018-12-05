//
// Created by nils.steinbuegl on 12/4/2018.
//

#include "SphereCollider.h"
#include "../../PhysicsSystem/PhysicsSystem.h"


namespace  TandenEngine {

    void SphereCollider::Register() {
        PhysicsSystem::RegisterColliderObject(this);
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