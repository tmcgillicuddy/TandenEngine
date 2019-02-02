//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_ENGINE_H
#define HWENGINE_ENGINE_H

#include <string>

#include "../Core/Timer/Timer.h"
#include "../Core/Input/Input.h"
#include "../Core/EventSystem/EventSystem.h"
#include "./RenderingSystem/RenderingSystem.h"
#include "./PhysicsSystem/PhysicsSystem.h"
#include "./Serialization/ProjectSettings.h"
#include "./Serialization/Serializer.h"
#include "ResourceManager/ResourceManager.h"
#include "Game.h"

namespace TandenEngine {

    class Engine : public EventListener {
    private:
        bool exitStatus = 0;

        void ProcessEvent(Event *) override;

        void ProcessEventKeyboard(KeyboardEvent *);

        std::string mProjectDirectory; //Directory to project folder

        ProjectSettings * mProjectSettings; //The instances project settings

        std::vector<Scene *> mLoadedScenes;

    public:
        static Game * mGame;

        Engine();

        void StartEngine();

        void RunEngine();

        void StopEngine();
    };

}
#endif //HWENGINE_ENGINE_H
