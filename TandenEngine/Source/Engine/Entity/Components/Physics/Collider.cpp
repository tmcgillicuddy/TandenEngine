//
// Created by nils.steinbuegl on 12/3/2018.
//

#include "Collider.h"
#include "../../../PhysicsSystem/PhysicsSystem.h"
#include "../../GameObject.h"


namespace TandenEngine {

    Collider::Collider() {
        //mTransform = dynamic_cast<Transform*>(mParentObject->GetComponent<Transform>());
    }

    void Collider::Register() {
        PhysicsSystem::RegisterColliderObject(this);
    }
}