//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_MODEL_H
#define HWENGINE_MODEL_H

#include <vector>

#include "MeshVertex.h"
#include "../Resource.h"

namespace TandenEngine {

    class Model : public Resource{
    public:
        Model();
        std::vector<MeshVertex> mVertexBuffer;
    };

}

#endif //HWENGINE_MODEL_H
