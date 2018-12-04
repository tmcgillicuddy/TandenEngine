//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_MATERIAL_H
#define TANDENENGINE_MATERIAL_H

#include "./Resource.h"

namespace TandenEngine {

    class Material : public Resource {
    public:
        Material();
        void SaveMaterial();
        static bool CheckIfSupported(std::string extension);

    };

}

#endif //TANDENENGINE_MATERIAL_H
