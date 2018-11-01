//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_RESOURCE_H
#define HWENGINE_RESOURCE_H

#include <string>

#include "./MetaData.h"

namespace TandenEngine {

    class Resource {
    public:
        Resource( const std::string ext ) :mFileExtension(ext){}

    protected:
        const std::string mFileExtension;
        MetaData * mMetaData;
    };

}

#endif //HWENGINE_RESOURCE_H
