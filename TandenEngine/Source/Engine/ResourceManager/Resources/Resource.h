//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_RESOURCE_H
#define HWENGINE_RESOURCE_H

#include <string>

#include "../MetaData.h"

namespace TandenEngine {

    class Resource {
        friend class ResourceManager;
    public:
        explicit Resource(DataType type){ mResourceType = type; }
        std::string GenerateFileName();
    private:
        DataType mResourceType;
        std::string fileName;
    };

}

#endif //HWENGINE_RESOURCE_H
