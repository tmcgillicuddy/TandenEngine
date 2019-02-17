//
// Created by thomas.mcgillicuddy on 10/31/2018.
//
#ifndef TANDENENGINE_SERIALIZER_H
#define TANDENENGINE_SERIALIZER_H

#include <stdio.h>
#include <windows.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>

#include "ProjectSettings.h"

namespace TandenEngine {

    class Serializer {
     private:
        static const std::string mFileBreak;
        // Will run through a directory and it's subdirectories to get any meta data
        static void GetMetaDataAtDir(std::string dir);
     public:
        static std::string mProjectDir, mAssetDir, mProjectSettingDir;
        // Creates a base project
        static void CreateProject(std::string projectName, std::string path);
        // Loads the entire project file from a file path
        static ProjectSettings * LoadProject(std::string projectDir);
        // Writes input data to a specific path anywhere in project
        static bool WriteString(std::string path, std::string data);
        // Writes input data to a specific path in the asset folder
        static bool WriteStringToAssetFolder(std::string path, std::string data);
        // Returns All the data in a file as one string
        static std::string GetFileData(std::string path);

        static void ImportFiles();
        static void CheckDir(std::vector<std::string> knownFiles, std::string dir);

        static std::vector<std::string> SeperateString(std::string input);
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_SERIALIZER_H
