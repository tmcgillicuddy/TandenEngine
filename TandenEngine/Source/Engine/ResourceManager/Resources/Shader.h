//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_SHADER_H
#define TANDENENGINE_SHADER_H

#include "Resource.h"

namespace TandenEngine {

    class Shader : public Resource{
    public:
        Shader();
        static bool CheckIfSupported(std::string extension);
    };

}

#endif //TANDENENGINE_SHADER_H
