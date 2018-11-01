//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_PROJECTSETTINGS_H
#define HWENGINE_PROJECTSETTINGS_H

#include <string>
#include <vector>

#include "../ResourceManager/Resource.h"
#include "../ResourceManager/SceneSettings.h"

namespace TandenEngine {

    class ProjectSettings {
        std::string mProjectName;
        std::vector<SceneSettings> mSceneFiles;
        std::vector<Resource> mResourceFiles;
    };

}

#endif //HWENGINE_PROJECTSETTINGS_H
