//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Serializer.h"

namespace TandenEngine {

    const std::string Serializer::mFileBreak  = "=======================\n";

     void Serializer::CreateProject(std::string projectName = "Untitled Project", std::string path = "./") {
        std::cout<<"Creating Project\n";

        //Create Base Project Folder
         if (CreateDirectory((path + "\\" + projectName).c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError())
         {
             // CopyFile(...)
         }
         else
         {
             // Failed to create directory.
             std::cout<<"Error creating base project folder\n";
         }

         //Create Assets Folder
         if (CreateDirectory((path + "\\" + projectName+ "\\Assets").c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError())
         {
             //Populate the assets folder
             std::string folderPath = path + "\\" + projectName + "\\Assets";
         }
         else
         {
             // Failed to create directory.
             std::cout<<"Error creating assets folder\n";
         }

         //Create Project Settings Folder
         if (CreateDirectory((path + "\\" + projectName + "\\ProjectSettings").c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError())
         {
             //Populate the project settings folder
             std::string folderPath = path + "\\" + projectName + "\\ProjectSettings";
             //SaveProject(newProj);
         }
         else
         {
             // Failed to create directory.
             std::cout<<"Error creating project settings folder\n";
         }

     }

    void Serializer::SaveProject(ProjectSettings * projectSettings) {
        std::ofstream fileStream;

        fileStream.open(projectSettings->mProjectName + projectSettings->mExtension);

        //Project file info

        fileStream << projectSettings->mProjectName << "\n";

        fileStream << mFileBreak;

        //Resource info

        for (auto const &resource : projectSettings->mResourceFiles)
        {

            fileStream << mFileBreak;
        }

        fileStream.close();
    }

    ProjectSettings * Serializer::LoadProject(std::string projectDir) {
        std::cout<< "Loading from " << projectDir << std::endl;

        int valid = 1; //Default to true

        DWORD ftyp = GetFileAttributesA(projectDir.c_str());

        if (ftyp == INVALID_FILE_ATTRIBUTES) //Not a valid directory
        {
            valid = 0;
        }
        else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) //Valid Directory
        {
            ftyp = GetFileAttributesA((projectDir + "/Assets/").c_str());
            if (ftyp == INVALID_FILE_ATTRIBUTES) //Not a valid Assets directory
            {
                valid = 0;
            }
            ftyp = GetFileAttributesA((projectDir + "/ProjectSettings/").c_str());
            if (ftyp == INVALID_FILE_ATTRIBUTES) //Not a valid Project settings directory
            {
                valid = 0;
            }
        }

        if(!valid) { //Ask to make a new project at directory
            std::cout << "No project at path, making a new one\n";
            std::cout << "New project name? ";
            std::string newName;
            std::cin >> newName;
            CreateProject(newName, projectDir);
        }

        //ProjectSettings *loadedProj;
        std::ifstream fileStream;
        fileStream.open(projectDir);
        if (!fileStream.is_open()) {

        } else //File exists
        {
           // loadedProj = new ProjectSettings();
            //fileStream >> loadedProj->mProjectName;
            //Load the resources for the project file
            std::string input;
            while (fileStream >> input) {
                std::cout << "New Resource\n";
                while (fileStream >> input && input != mFileBreak) {
                    std::cout << input << std::endl;
                }
            }
        }
        fileStream.close();

        return nullptr;
    }

}