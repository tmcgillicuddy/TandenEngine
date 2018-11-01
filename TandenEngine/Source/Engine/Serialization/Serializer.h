//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_SERIALIZER_H
#define HWENGINE_SERIALIZER_H

#include <string>
#include <fstream>

#include "ProjectSettings.h"
#include "../ResourceManager/SceneSettings.h"
#include "../ResourceManager/PrefabSettings.h"

#include "../Entity/Scene.h"

namespace TandenEngine {

    class Serializer {
    public:
        static ProjectSettings * CreateProject(std::string projectName);
        static void SaveProject(ProjectSettings * projectSettings); //Saves the entire project file (references to resources)
        static ProjectSettings * LoadProject(std::string projectDir); //Loads the entire project file from a file path

        static void SaveScene(Scene sceneSettings); //Save the scene to the a scene settings file
        static void LoadScene(SceneSettings sceneSettings); //Loads scene settings from given scene setting file

        static void SavePrefab(PrefabSettings prefabSettings); //Save prefab settings to the pointed prefab file
        static void LoadPrefab(PrefabSettings prefabSettings); //Loads prefab settings from the given prefab file
    };

}

#endif //HWENGINE_SERIALIZER_H
