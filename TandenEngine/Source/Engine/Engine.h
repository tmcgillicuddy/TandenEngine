//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#ifndef HWENGINE_ENGINE_H
#define HWENGINE_ENGINE_H

#include "../Core/Timer/Timer.h"
#include "../Core/Input/Input.h"
#include "../Core/EventSystem/EventSystem.h"
#include "./RenderingSystem/RenderingSystem.h"
#include "./PhysicsSystem/PhysicsSystem.h"
#include "./Entity/Scene.h"

namespace TandenEngine {

    class Engine : public EventListener {
    private:
        bool exitStatus = 0;

        void ProcessEvent(Event *) override;

        void ProcessEventKeyboard(KeyboardEvent *);

        std::vector<Scene *> mLoadedScenes;

    public:
        Engine();

        void StartEngine();

        void RunEngine();

        void StopEngine();

    };

}
#endif //HWENGINE_ENGINE_H
