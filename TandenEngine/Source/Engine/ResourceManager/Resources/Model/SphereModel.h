//
// Created by Thomas on 1/19/2019.
//

#ifndef TANDENENGINE_SPHEREMODEL_H
#define TANDENENGINE_SPHEREMODEL_H

#include "Model.h"

namespace TandenEngine {

    class SphereModel : public Model {
     private:
        const int mSlices = 8, mStacks = 5;
        float mRadius = 1;
     public:
        SphereModel();
        void LoadModel();
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_SPHEREMODEL_H
