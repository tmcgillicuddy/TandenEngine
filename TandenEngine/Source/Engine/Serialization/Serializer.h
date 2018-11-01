//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_SERIALIZER_H
#define HWENGINE_SERIALIZER_H

#include <string>

#include "ProjectSettings.h"

class Serializer {
public:
    void SaveProject(ProjectSettings projectSettings); //Saves the entire project file (references to resources)
    void LoadProject(std::string projectName); //Loads the entire project file from a file path

    //void SaveScene(SceneSettings sceneSettings); //Save the scene settings to the current project file
    //void LoadScene(SceneSettings sceneSettings); //Loads scene settings from given scene setting file
};


#endif //HWENGINE_SERIALIZER_H
