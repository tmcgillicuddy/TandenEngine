//
// Created by thomas.mcgillicuddy on 10/31/2018.
//
#ifndef HWENGINE_SERIALIZER_H
#define HWENGINE_SERIALIZER_H

#include <string>
#include <fstream>
#include <windows.h>
#include <filesystem>
#include<stdio.h>
#include <iostream>

#include "ProjectSettings.h"


namespace TandenEngine {

    class Serializer
    {
    private:
        static const std::string mFileBreak;
        static void GetMetaDataAtDir(std::string dir); //Will run through a directory and it's subdirectories to get any meta data
    public:
        static std::string mProjectDir, mAssetDir, mProjectSettingDir;
        static void CreateProject(std::string projectName, std::string path); //Creates a base project
        static ProjectSettings * LoadProject(std::string projectDir); //Loads the entire project file from a file path
        static bool WriteString(std::string path, std::string data); //Writes input data to a specific path anywhere in project
        static bool WriteStringToAssetFolder(std::string path, std::string data); //Writes input data to a specific path in the asset folder
        static std::string GetFileData(std::string path); //Returns All the data in a file as one string

        static void ImportFiles();
        static void CheckDir(std::vector<std::string> knownFiles, std::string dir);

        static std::vector<std::string> SeperateString(std::string input);
    };

}

#endif //HWENGINE_SERIALIZER_H
