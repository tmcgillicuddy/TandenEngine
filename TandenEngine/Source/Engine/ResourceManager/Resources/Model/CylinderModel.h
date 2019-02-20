//
// Created by Thomas on 1/19/2019.
//

#ifndef TANDENENGINE_CYLINDERMODEL_H
#define TANDENENGINE_CYLINDERMODEL_H

#include "Model.h"

namespace TandenEngine {

    class CylinderModel : public Model {
     private:
        const int mSlices = 8, mStacks = 2;
        const float mHeight = 2, mRadius = 1;
     public:
        CylinderModel();
        void LoadModel();
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_CYLINDERMODEL_H
