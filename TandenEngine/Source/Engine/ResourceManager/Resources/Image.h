//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_IMAGE_H
#define TANDENENGINE_IMAGE_H

#include "./Resource.h"
#include "../MetaData.h"

namespace TandenEngine {

    class Image : public Resource {
    public:
        Image();
        Image(MetaData* metaData);
        static bool CheckIfSupported(std::string extension);
    };

}

#endif //TANDENENGINE_IMAGE_H
