//
// Created by nils.steinbuegl on 12/3/2018.
//

#include "Collider.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"
#include "../../GameObject.h"


namespace TandenEngine {

    Collider::Collider() {
        std::cout <<"Collider";
    }

    void Collider::Register() {
        PhysicsSystem::RegisterColliderObject(this);
    }

    void Collider::Update() {
    }

}