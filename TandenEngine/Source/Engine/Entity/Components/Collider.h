//
// Created by nils.steinbuegl on 12/3/2018.
//

#ifndef TANDENENGINE_COLLIDER_H
#define TANDENENGINE_COLLIDER_H

#include "Component.h"

namespace TandenEngine {

    class Collider : public Component {
        public:
            Collider() {};
            ~Collider() {};

            void Update() {};

            int whatever = 0;

    };

}


#endif //TANDENENGINE_COLLIDER_H
