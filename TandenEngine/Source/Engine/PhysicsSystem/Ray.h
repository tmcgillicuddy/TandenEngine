//
// Created by Thomas on 2018-12-25.
//

#ifndef TANDENENGINE_RAY_H
#define TANDENENGINE_RAY_H

#include <NilsMath.h>

namespace TandenEngine
{
    class Ray
    {
        public:
        Ray(); //Base Constructor
//        Ray(const Vector3 &origin, const Vector3 &dir, float tMax = Infinity, float time = 0.0f, const Medium *medium = nullptr);

        //Vector3 operator()(float time) const {return mOrigin+mDirection*time; };

        //Data
        Vector3 mOrigin; //Origin of the ray
        Vector3 mDirection; //Direction the ray is moving
        mutable float mTMax; //Max value time can be before end of ray
        float mTime; //Time/progress when walking the ray
      //  const Medium *mMedium; //Material the ray is passing through
    };
}

#endif //TANDENENGINE_RAY_H