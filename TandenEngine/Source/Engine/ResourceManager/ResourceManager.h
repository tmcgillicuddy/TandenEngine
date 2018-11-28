//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#ifndef TANDENENGINE_RESOURCEMANAGER_H
#define TANDENENGINE_RESOURCEMANAGER_H

#include "Resources/Resource.h"
#include "Resources/Shader.h"
#include "Resources/Material.h"
#include "Resources/Image.h"
#include "Resources/Prefab.h"
#include "Resources/AudioClip.h"
#include "Resources/Model/Model.h"

namespace TandenEngine {
    class ResourceManager {
    public:
        static Resource* GenerateResourceFromMetaData(MetaData * metaData);
    };
}

#endif //TANDENENGINE_RESOURCEMANAGER_H
