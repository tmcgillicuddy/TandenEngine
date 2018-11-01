//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_SCENE_H
#define HWENGINE_SCENE_H

#include <vector>
#include <iostream>

//Tanden Engine Classes
#include "GameObject.h"
#include "../ResourceManager/SceneSettings.h"

namespace TandenEngine {

    class Scene {
    private:
        std::vector<std::unique_ptr<GameObject>> mGameObjects;

        SceneSettings * mSceneSettings;

    public:

        Scene(); //Just create a new scene (generates scene setting file)
        Scene(SceneSettings*); //Create scene from scene settings file

        GameObject *CreateGameObject();

        bool DestroyGameObject();

        GameObject *FindGameObject();

        void Update();

    };

}

#endif //HWENGINE_SCENE_H
