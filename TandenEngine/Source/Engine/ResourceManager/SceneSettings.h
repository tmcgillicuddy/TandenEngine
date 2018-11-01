//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_SCENESETTINGS_H
#define HWENGINE_SCENESETTINGS_H

#include <string>

#include "./Resource.h"

namespace TandenEngine {

    class SceneSettings : public Resource {
        friend class Scene;
        std::string mSceneName = "Untitled";
        SceneSettings() : Resource(".scene"){}

    };

}

#endif //HWENGINE_SCENESETTINGS_H
