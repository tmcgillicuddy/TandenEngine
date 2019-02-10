//
// Created by thomas.mcgillicuddy on 2/10/2019.
//

#ifndef TANDENENGINE_PRIMITIVE_H
#define TANDENENGINE_PRIMITIVE_H

#include "SphereModel.h"
#include "CubeModel.h"
#include "CylinderModel.h"

namespace TandenEngine {
    class Primitive {
        static CubeModel Cube;
        static SphereModel Sphere;
        static CylinderModel Cylinder;
    };
}

#endif  // TANDENENGINE_PRIMITIVE_H
