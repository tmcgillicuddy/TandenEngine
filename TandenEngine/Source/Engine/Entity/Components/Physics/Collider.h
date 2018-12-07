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

            void Update() override;

            void Register() override;

            std::string ToString() override {return std::string();};
            Component * ConvertFromString(std::vector<std::string>) override { return NULL;}; //Takes in some string data and will output a Collider object
    };

}


#endif //TANDENENGINE_COLLIDER_H
