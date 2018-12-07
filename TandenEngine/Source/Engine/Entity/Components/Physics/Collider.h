//
// Created by nils.steinbuegl on 12/3/2018.
//

#ifndef TANDENENGINE_COLLIDER_H
#define TANDENENGINE_COLLIDER_H

#include "../Component.h"
#include "Vector3.h"
#include <iostream>
#include "../Transform.h"

namespace TandenEngine {

    class GameObject;

    class Collider : public Component {
        public:
            friend class PhysicsSystem;

            Collider();
            ~Collider() {};

            //Component Overrides
            void Register() override;
    };
}


#endif //TANDENENGINE_COLLIDER_H
