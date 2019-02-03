//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHVERTEX_H
#define HWENGINE_MESHVERTEX_H

#include "NilsMath.h"

namespace TandenEngine {

    class MeshVertex {
    public:
        vec3 mPos;
        vec2 mUV;
        vec3 mNormal;
        vec3 mTangent;
        vec3 mColor;

        bool operator==(const MeshVertex& other) const {
            return mPos == other.mPos && mColor == other.mColor && mUV == other.mUV;
        }
    };
}

namespace std {
    template<> struct ::std::hash<TandenEngine::MeshVertex> {
        size_t operator()(TandenEngine::MeshVertex const& vertex) const {
            return ((::std::hash<TandenEngine::vec3>()(vertex.mPos  ) ^
                     (::std::hash<TandenEngine::vec3>()(vertex.mColor) << 1)) >> 1) ^
                   (::std::hash<TandenEngine::vec2>()(vertex.mUV) << 1);
        }
    };
}

#endif //HWENGINE_MESHVERTEX_H
