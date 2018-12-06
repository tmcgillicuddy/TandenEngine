//
// Created by nils.steinbuegl on 12/4/2018.
//

#ifndef TANDENENGINE_SPHERECOLLIDER_H
#define TANDENENGINE_SPHERECOLLIDER_H

#include "../../../../Core/Math/NilsMath.h"
#include "Collider.h"

namespace TandenEngine {

    class SphereCollider : public Collider {
    public:
        SphereCollider() {};
        ~SphereCollider() {};

        SphereCollider( Vector3 position, float radius) {
            mPosition = position, mRadius = radius;

        }

        Vector3 mPosition;
        float mRadius;

        void Register() override;

        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string>) override; //Takes in some string data and will output a physicsComponent object

    };

}


#endif //TANDENENGINE_SPHERECOLLIDER_H
