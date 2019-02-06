//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef TANDENENGINE_PROJECTSETTINGS_H
#define TANDENENGINE_PROJECTSETTINGS_H

#include <string>
#include <vector>

namespace TandenEngine {

    class ProjectSettings {
        friend class Serializer;
        const std::string mExtension = ".project";
        std::string mProjectName;
     public:
        void PrintProjectInfo();
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_PROJECTSETTINGS_H
