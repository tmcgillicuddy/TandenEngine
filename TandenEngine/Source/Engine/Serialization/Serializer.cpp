//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "Serializer.h"

namespace TandenEngine {

    const std::string Serializer::mFileBreak  = "=======================\n";

    ProjectSettings * Serializer::CreateProject(std::string projectName = "Untitled Project") {
        std::cout<<"Creating Project\n";

        ProjectSettings * newProj = new ProjectSettings();

        newProj->mProjectName = projectName;

        SaveProject(newProj);

        return newProj;
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

        int valid = projectDir.find(".project");
        
        if(valid < 1) {
            projectDir += ".project";
        }

        ProjectSettings * loadedProj;

        std::ifstream fileStream;

        fileStream.open(projectDir);

        if(!fileStream.is_open())
        {
            std::cout << "No project file at path, making a new one\n";
            std::cout << "New project name? ";
            std::string newName;
            std::cin >> newName;
            loadedProj = CreateProject(newName);
        }
        else //File exists
        {
            loadedProj = new ProjectSettings();
            fileStream >> loadedProj->mProjectName;

            //Load the resources for the project file
            std::string input;
            while (fileStream >> input)
            {
                std::cout << "New Resource\n";
                while(fileStream >> input && input != mFileBreak)
                {
                    std::cout << input << std::endl;
                }
            }
        }

        fileStream.close();

        return loadedProj;
    }

}