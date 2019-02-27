#include "Serializer.h"
#include <sstream>
#include <algorithm>
#include <iterator>
#include <experimental/filesystem>

#include "../ResourceManager/ResourceManager.h"

namespace TandenEngine {

    const std::string Serializer::mFileBreak  = "=======================\n";
    std::string Serializer::mProjectDir, Serializer::mAssetDir, Serializer::mProjectSettingDir;

     void Serializer::CreateProject(std::string projectName = "Untitled Project",
             std::string path = "./") {
        std::cout << "Creating Project\n";
        std::cout << path;
        // Create Base Project Folder
         if (CreateDirectory((path + "\\" + projectName).c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError()) {
         } else {
             // Failed to create directory.
             std::cout << "Error creating base project folder\n";
         }

         // Create Assets Folder
         if (CreateDirectory((path + "\\" + projectName+ "\\Assets").c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError()) {
             // Populate the assets folder
             std::string folderPath = path + "\\" + projectName + "\\Assets";
         } else {
             // Failed to create directory.
             std::cout << "Error creating assets folder\n";
         }

         // Create Project Settings Folder
         if (CreateDirectory((path + "\\" + projectName + "\\ProjectSettings").c_str(), NULL) ||
             ERROR_ALREADY_EXISTS == GetLastError()) {
             // Populate the project settings folder
             std::string folderPath = path + "\\" + projectName + "\\ProjectSettings\\";
             // Project file
             {
                 ProjectSettings *projectSettings = new ProjectSettings();
                 // Setup object
                 projectSettings->mProjectName = projectName;

                 // Write to file
                 std::ofstream fileStream;
                 fileStream.open(folderPath + "ProjectSettings" + projectSettings->mExtension);

                 // Write Project settings to file

                 fileStream << projectSettings->mProjectName << "\n";

                 fileStream << mFileBreak;

                 fileStream.close();
             }
         } else {
             // Failed to create directory.
             std::cout << "Error creating project settings folder\n";
         }
     }

    ProjectSettings * Serializer::LoadProject(std::string projectDir) {
        std::cout<< "Loading from " << projectDir << std::endl;

        int valid = 1;  // Default to true

        DWORD ftyp = GetFileAttributesA(projectDir.c_str());

        if (ftyp == INVALID_FILE_ATTRIBUTES) {  // Not a valid directory
            valid = 0;
        } else if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {  // Valid Directory
            ftyp = GetFileAttributesA((projectDir + "/Assets/").c_str());
            if (ftyp == INVALID_FILE_ATTRIBUTES) {  // Not a valid Assets directory
                valid = 0;
            }
            ftyp = GetFileAttributesA((projectDir + "/ProjectSettings/").c_str());
            if (ftyp == INVALID_FILE_ATTRIBUTES) {  // Not a valid Project settings directory
                valid = 0;
            }
        }

        if (!valid) {  // Ask to make a new project at directory
            std::cout << "No project at path, making a new one\n";
            std::cout << "New project name? ";
            std::string newName;
            std::cin >> newName;
            projectDir = "./";
            CreateProject(newName, projectDir);
            projectDir = projectDir + newName;  // Make sure to adjust the project directory
        }

        ProjectSettings *loadedProj = new ProjectSettings();

        std::ifstream fileStream;

        fileStream.open(projectDir + "\\ProjectSettings\\ProjectSettings" + loadedProj->mExtension);

        if (!fileStream.is_open()) {
            std::cout<< "Error Loading Project Settings File\n";
        } else {  // File exists
            std::cout<< "Found Project Settings File\n";
            fileStream >> loadedProj->mProjectName;
        }
        fileStream.close();

        mProjectDir = projectDir;
        mAssetDir = projectDir + "\\Assets\\";
        mProjectSettingDir = projectDir + "\\ProjectSettings\\";

        ImportFiles();

        return loadedProj;
    }

    void Serializer::GetMetaDataAtDir(std::string dir) {
        std::string extension = "*.meta";  // Extension for meta data
        std::string name, junk;
        for (auto & p : std::experimental::filesystem::recursive_directory_iterator(dir)) {
            name = p.path().u8string();
            if (name.substr(name.find_last_of(".") + 1) == "meta") {
                std::ifstream fileStream;
                fileStream.open(name);
                if (!fileStream.is_open()) {
                    std::cout<< "Error opening meta data\n";
                } else {
                    // Create meta data object from file
                    MetaData * newMeta = new MetaData();
                    std::getline(fileStream, newMeta->mFileDir);
                    fileStream >> newMeta->mGuid;
                    std::getline(fileStream, junk);
                    std::cout << newMeta->mGuid;
                    int inputEnum;
                    fileStream >> inputEnum;  // TODO(Thomas) error check for missing data
                    newMeta->mFileType = (ResourceType)inputEnum;
                    // Test generate resource from meta data
                    Resource * newResouce = ResourceManager::GenerateResourceFromMetaData(newMeta);
                    if (newResouce != nullptr) {
                        // Add meta data to resource manager to track
                        ResourceManager::AddMetaData(newMeta);
                    } else {
                        std::cout << "Couldn't generate resource from meta data: "
                        << name << std::endl;
                        std::remove(name.c_str());
                    }
                }
            }
        }
    }

    bool Serializer::WriteString(std::string path, std::string data) {
        std::fstream newFile;

        newFile.open(path, std::fstream::out);

        newFile << data;

        newFile.close();
        return true;
    }

    std::vector<std::string> Serializer::SeperateString(std::string input) {
         std::vector<std::string> output;
        std::stringstream ss(input);
        std::string item;
        while (std::getline(ss, item, '\n')) {
            if (item.length() > 0) {
                std::stringstream iss(item);
                for (std::string item; iss >> item; )
                    output.push_back(item);
            }
        }

        return output;
    }

    bool Serializer::WriteStringToAssetFolder(std::string path, std::string data) {
        std::fstream newFile;

        newFile.open(mAssetDir+ path, std::fstream::out);

        newFile << data;

        newFile.close();
        return true;
    }

    std::string Serializer::GetFileData(std::string path) {
         std::ifstream newFile;
         newFile.open(path);

         std::string data = "", input;
        while (std::getline(newFile, input)) {  // Read ALL the data to the output string
            data += input + '\n';
        }
        newFile.close();

        return data;
    }

    void Serializer::ImportFiles() {
        // Load up any existing meta files
        GetMetaDataAtDir(mAssetDir);

        // Discover any new files and generate new meta data for them (if supported)
        std::vector<std::string> exsistingFiles = ResourceManager::GetAllFoundResourceFiles();
        CheckDir(exsistingFiles, mAssetDir);
    }

    void Serializer::CheckDir(std::vector<std::string> knownFiles, std::string dir) {
        std::string extension = "*.meta";  // Extension for meta data
        std::string name;
        std::string tempDir = dir;
        std::replace(tempDir.begin(), tempDir.end(), '/', '\\');
        for (auto & p : std::experimental::filesystem::recursive_directory_iterator(tempDir)) {
            name = p.path().u8string();
            bool isCovered = false;  // Flag to know if meta file for this resource already exists
            if (name.substr(name.find_last_of(".") + 1) != "meta") {
                for (auto metaName : knownFiles) {
                    if (name.compare(metaName) == 0) {
                        isCovered = true;
                        break;
                    }
                }

                if (!isCovered) {  // If this file doesn't have associated meta data
                    // Gets the file's extension
                    std::string extension = p.path().extension().string();
                    ResourceType resourceType = ResourceManager::CheckExtensionSupported(extension);
                    if (resourceType != ResourceType::INVALID) {
                        std::cout << "Generating Meta Data "
                        << static_cast<int>(resourceType)
                        << std::endl;

                        ResourceManager::GenerateNewMetaData(
                                p.path().filename().string(),
                                resourceType);
                    } else {
                        std::cout << name << " is an invalid file type\n";
                    }
                }
            }
        }
    }
}  // namespace TandenEngine
