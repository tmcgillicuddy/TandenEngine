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
        Vector3 mXOrigin, mYOrigin;
        Vector3 mXDirection, mYDirection;

    };

}

#endif //TANDENENGINE_RAYDIFFERENTIAL_H
