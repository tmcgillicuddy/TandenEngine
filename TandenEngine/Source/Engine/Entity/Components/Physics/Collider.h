//
// Created by nils.steinbuegl on 12/3/2018.
//

#ifndef TANDENENGINE_COLLIDER_H
#define TANDENENGINE_COLLIDER_H

#include "../Component.h"
#include "Vector3.h"
#include <iostream>

namespace TandenEngine {

    class Collider : public Component {
        public:
            friend class PhysicsSystem;

            Collider() {};
            ~Collider() {};

            virtual void Update() {};

        // TODO inherit form base GameObj transform
        Vector3 mPosition;
        Vector3 mRotation;
        Vector3 mSize;

        void Register() override;

        std::string ToString() override {return std::string();};
        Component * ConvertFromString(std::vector<std::string>) override { return NULL;}; //Takes in some string data and will output a Collider object
    };

}


#endif //TANDENENGINE_COLLIDER_H
