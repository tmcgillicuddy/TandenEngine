//
// Created by thomas.mcgillicuddy on 2/10/2019.
//

#ifndef TANDENENGINE_RAYHIT_H
#define TANDENENGINE_RAYHIT_H

#include "NilsMath.h"

namespace TandenEngine {

    class RayHit {
     public:
        vec2 mUV;  // the UV of the hit point
        vec3 mNormal;  // the normal of the hit surface
        vec3 mPoint;  // Where in ws did the hit intersect
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_RAYHIT_H
