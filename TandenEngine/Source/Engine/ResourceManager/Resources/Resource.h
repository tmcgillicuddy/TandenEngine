//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_RESOURCE_H
#define TANDENENGINE_RESOURCE_H

#include <string>

#include "../MetaData.h"
#include "../../Serialization/Serializer.h"

namespace TandenEngine {

    class Resource {
        friend class ResourceManager;
     public:
        explicit Resource() { }
        std::string GenerateFileName();
        ResourceType mResourceType;
        std::string fileName;
        MetaData * mMetaData;
    }

}  // namespace TandenEngine

#endif  // TANDENENGINE_RESOURCE_H
