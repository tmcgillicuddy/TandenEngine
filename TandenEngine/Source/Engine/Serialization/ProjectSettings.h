//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_PROJECTSETTINGS_H
#define HWENGINE_PROJECTSETTINGS_H

#include <string>
#include <vector>

#include "SceneSettings.h"

namespace TandenEngine {

    class ProjectSettings {
        std::string projectName;
        std::vector<SceneSettings> sceneFiles;
    };

}

#endif //HWENGINE_PROJECTSETTINGS_H
