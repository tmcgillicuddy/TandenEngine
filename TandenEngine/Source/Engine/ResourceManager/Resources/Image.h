//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_IMAGE_H
#define TANDENENGINE_IMAGE_H

#include "./Resource.h"

namespace TandenEngine {

    class Image : public Resource {
    public:
        Image();
        static bool CheckIfSupported(std::string extension);
    };

}

#endif //TANDENENGINE_IMAGE_H
