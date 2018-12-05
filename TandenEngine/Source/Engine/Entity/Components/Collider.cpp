//
// Created by nils.steinbuegl on 12/3/2018.
//

#include "Collider.h"
#include "../../PhysicsSystem/PhysicsSystem.h"


namespace TandenEngine {

    void Collider::Register() {
        PhysicsSystem::RegisterColliderObject(this);
    }
}