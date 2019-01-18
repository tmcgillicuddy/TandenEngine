//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MESHVERTEX_H
#define HWENGINE_MESHVERTEX_H

#include "NilsMath.h"

namespace TandenEngine {

    class MeshVertex {
    public:
        Vector3 mPos;
        Vector2 mUV;
        Vector3 mNormal;
        Vector3 mTangent;
        Vector3 mColor;

        bool operator==(const MeshVertex& other) const {
            return mPos == other.mPos && mColor == other.mColor && mUV == other.mUV;
        }

        //Custom hashing function
        //namespace std {
        //    template<> class ::std::hash<TandenEngine::MeshVertex> {
        //        size_t operator()(TandenEngine::MeshVertex const& vertex) const {
        //            return ((hash<TandenEngine::Vector3>()(vertex.mPos) ^
        //                    (hash<TandenEngine::Vector3>()(vertex.mColor) << 1)) >> 1)^
        //                    (hash<TandenEngine::Vector2>()(vertex.mUV) << 1);
        //        }
        //    };
        //}
    };

}

#endif //HWENGINE_MESHVERTEX_H
