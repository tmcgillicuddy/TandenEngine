//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHVERTEX_H
#define HWENGINE_MESHVERTEX_H

#include "../Math/NilsMath.h"

namespace TandenEngine {

    class MeshVertex {
    private:
        Vector3 mPos;
        Vector2 mUV;
        Vector3 mNormal;
        Vector3 mTangent;
    };

}

#endif //HWENGINE_MESHVERTEX_H
