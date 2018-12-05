//
// Created by nils.steinbuegl on 12/3/2018.
//

#ifndef TANDENENGINE_BOXCOLLIDER_H
#define TANDENENGINE_BOXCOLLIDER_H

#include "../../../Core/Math/NilsMath.h"
#include "Collider.h"

namespace TandenEngine {

    class BoxCollider : public Collider {
        public:
            BoxCollider() {};
            ~BoxCollider() {};

            BoxCollider( Vector3 position, Vector3 rotation, Vector3 scale) {
                mPosition = position, mRotation = rotation, mSize = scale;

            }

            Vector3 mPosition;
            Vector3 mRotation;
            Vector3 mSize;


        void Register() override;

        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string>) override; //Takes in some string data and will output a physicsComponent object

    };

}


#endif //TANDENENGINE_BOXCOLLIDER_H
