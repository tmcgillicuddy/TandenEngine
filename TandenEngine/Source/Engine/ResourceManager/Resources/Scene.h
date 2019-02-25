//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_SCENE_H
#define HWENGINE_SCENE_H

#include <vector>
#include <iostream>

#include "../../Entity/GameObject.h"
#include "./Resource.h"

namespace TandenEngine {

    class Scene : public Resource {
     public:
        std::vector<std::unique_ptr<GameObject>> mGameObjects;
        Scene();  // Just create a new scene (generates scene setting file)

        Scene(MetaData* inputMeta);

        GameObject *CreateGameObject();  // Creates a new game object in scene

        bool DestroyGameObject();  // Destroys game object in scene

        GameObject *FindGameObject();  // Finds game object in scene

        void Update();  // Base update function

        void SaveScene();  // Saves scene to scene file (creates if non existent)

        static bool CheckIfSupported(std::string extension);
    };
}  // namespace TandenEngine

#endif  // HWENGINE_SCENE_H
