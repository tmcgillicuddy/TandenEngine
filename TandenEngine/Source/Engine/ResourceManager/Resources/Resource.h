//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_RESOURCE_H
#define HWENGINE_RESOURCE_H

#include <string>

#include "../MetaData.h"
#include "../../Serialization/Serializer.h"

namespace TandenEngine {

    class Resource {
        friend class ResourceManager;
    public:

        explicit Resource(){ };
        std::string GenerateFileName();
        ResourceType mResourceType;
        std::string fileName;
    };

}

#endif //HWENGINE_RESOURCE_H
