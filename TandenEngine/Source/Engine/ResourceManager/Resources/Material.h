//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_MATERIAL_H
#define TANDENENGINE_MATERIAL_H

#include "./Resource.h"
#include "../MetaData.h"

namespace TandenEngine {

    class Material : public Resource {
     public:
        Material();
        Material(MetaData * metaData);
        void SaveMaterial();
        static bool CheckIfSupported(std::string extension);
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_MATERIAL_H
