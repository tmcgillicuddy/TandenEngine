//
// Created by nils.steinbuegl on 12/3/2018.
//

#ifndef TANDENENGINE_BOXCOLLIDER_H
#define TANDENENGINE_BOXCOLLIDER_H

#include "../../../../Core/Math/NilsMath.h"
#include "Collider.h"

namespace TandenEngine {

    class BoxCollider : public Collider {
        public:
            BoxCollider();
            ~BoxCollider();

            BoxCollider( Vector3 position, Vector3 rotation, Vector3 size) {
                mPosition = position, mRotation = rotation, mSize = size;
            }

            void Update() override;

            Vector3 mPosition;
            Vector3 mRotation;
            Vector3 mSize = Vector3(1.0, 1.0, 1.0);

            std::unique_ptr<Component> Clone() override;

            std::string ToString() override;
            Component * ConvertFromString(std::vector<std::string>) override; //Takes in some string data and will output a BoxCollider object
    };

}


#endif //TANDENENGINE_BOXCOLLIDER_H
