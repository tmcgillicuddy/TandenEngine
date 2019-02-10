//
// Created by Thomas on 2018-12-25.
//

#ifndef TANDENENGINE_RAYDIFFERENTIAL_H
#define TANDENENGINE_RAYDIFFERENTIAL_H

#include "Ray.h"

namespace TandenEngine {

    class RayDifferential : public Ray {
     public:
        bool mHasDifferential;
        vec3 mXOrigin, mYOrigin;
        vec3 mXDirection, mYDirection;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_RAYDIFFERENTIAL_H
