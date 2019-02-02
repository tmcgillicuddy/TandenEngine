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

            BoxCollider(vec3 position, vec3 rotation, vec3 scale);

            //Component Overrides
            void Update() override;
            std::unique_ptr<Component> Clone() override;
            std::string ToString() override;
            Component * ConvertFromString(std::vector<std::string> input) override;//Takes in some string data and will output a BoxCollider object
    };

}


#endif //TANDENENGINE_BOXCOLLIDER_H
