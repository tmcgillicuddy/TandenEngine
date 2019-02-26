//
// Created by nils.steinbuegl on 12/3/2018.
//

#ifndef TANDENENGINE_COLLIDER_H
#define TANDENENGINE_COLLIDER_H

#include <iostream>
#include "../Component.h"
#include "Vectors/vec3.h"
#include "../Transform.h"

namespace TandenEngine {

    class GameObject;

    class Collider : public Component {
     public:
        friend class PhysicsSystem;

        Collider();
        ~Collider() {}

        vec3 mLocalPosition;
        vec3 mGlobalPosition;
        vec3 mLocalRotation;
        vec3 mGlobalRotation;
        vec3 mScale = vec3(1.0, 1.0, 1.0);


        // Component Overrides
        void Register() override;

        void GenGUI() override {};
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_COLLIDER_H
