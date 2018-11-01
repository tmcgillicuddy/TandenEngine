//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "ProjectSettings.h"

#include "Serializer.h"

namespace  TandenEngine {

    void ProjectSettings::AddResource(TandenEngine::Resource newResouce) {
        mResourceFiles.emplace_back(newResouce);

        Serializer::SaveProject(this);
    }

    void ProjectSettings::PrintProjectInfo() {
        std::cout << "Project Name: " << mProjectName << std::endl;
        std::cout << "Project Resource Count: " << mResourceFiles.size() << std::endl;
    }
}