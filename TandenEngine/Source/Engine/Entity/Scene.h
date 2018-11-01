//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_SCENE_H
#define HWENGINE_SCENE_H

#include <vector>
#include <iostream>

//HWEngine Classes
#include "GameObject.h"

namespace TandenEngine {

    class Scene {
    private:
        std::vector<std::unique_ptr<GameObject>> mGameObjects;
    public:
        GameObject *CreateGameObject();

        bool DestroyGameObject();

        GameObject *FindGameObject();

        void Update();

    };

}

#endif //HWENGINE_SCENE_H
