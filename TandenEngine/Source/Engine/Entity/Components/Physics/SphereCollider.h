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
        SphereCollider();
        ~SphereCollider();

        SphereCollider(vec3 position, float radius);

        void Update() override;

        float mRadius = 1.0;

        std::unique_ptr<Component> Clone() override;

        std::string ToString() override;
        // Takes in some string data and will output a physicsComponent object
        Component * ConvertFromString(std::vector<std::string>) override;

        void GenGUI() override;
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_SPHERECOLLIDER_H
