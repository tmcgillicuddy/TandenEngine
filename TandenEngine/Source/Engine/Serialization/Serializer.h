//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef HWENGINE_SERIALIZER_H
#define HWENGINE_SERIALIZER_H

#include <string>
#include <fstream>
#include <windows.h>
#include <filesystem>

#include "ProjectSettings.h"
#include "../ResourceManager/ResourceManager.h"
#include "../ResourceManager/Resources/Scene.h"

namespace TandenEngine {

    class Serializer
    {
    private:
        static const std::string mFileBreak;

        static void GetMetaDataAtDir(ProjectSettings * parentSettings, std::string dir); //Will run through a directory and it's subdirectories to get any meta data
    public:
        static void CreateProject(std::string projectName, std::string path);
        static ProjectSettings * LoadProject(std::string projectDir); //Loads the entire project file from a file path

    };

}

#endif //HWENGINE_SERIALIZER_H
