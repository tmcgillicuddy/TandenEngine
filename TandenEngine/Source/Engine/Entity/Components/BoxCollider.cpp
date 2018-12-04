//
// Created by nils.steinbuegl on 12/3/2018.
//

#include "BoxCollider.h"
#include "../../PhysicsSystem/PhysicsSystem.h"


namespace  TandenEngine {

    void BoxCollider::Register() {
        PhysicsSystem::RegisterColliderObject(this);
    }

    std::string BoxCollider::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        return data;
    }

    Component *BoxCollider::ConvertFromString(std::vector<std::string>) {
        return NULL;
    }
}