//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHVERTEX_H
#define HWENGINE_MESHVERTEX_H

#include "NilsMath.h"

namespace TandenEngine {

    class MeshVertex {
    private:
        vec3 mPos;
        vec2 mUV;
        vec3 mNormal;
        vec3 mTangent;
    };

}

#endif //HWENGINE_MESHVERTEX_H
