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
                maxX = mPosition.x + mSize.x/2;
                minX = mPosition.x - mSize.x/2;
                maxY = mPosition.y + mSize.y/2;
                minY = mPosition.y - mSize.y/2;
                maxZ = mPosition.z + mSize.z/2;
                minZ = mPosition.z - mSize.z/2;
            }

            Vector3 mPosition;
            Vector3 mRotation;
            Vector3 mSize;

            // TODO These should update when the object changes
            float maxX;
            float minX;
            float maxY;
            float minY;
            float maxZ;
            float minZ;

        void Register() override;

        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string>) override; //Takes in some string data and will output a physicsComponent object

    };

}


#endif //TANDENENGINE_BOXCOLLIDER_H
