//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_GAMEOBJECT_H
#define HWENGINE_GAMEOBJECT_H

//STD Classes
#include <vector>
#include <utility> //smart pointers
#include <memory>
#include <algorithm>
#include <iostream>

//HWEngine classes
#include "Components/Component.h"

namespace TandenEngine {

    class GameObject { //Game Objects always have at least a transform component
        friend class Prefab;
    private:
        std::string mName = "Test Object";
        std::vector<std::unique_ptr<Component>> mComponents; //TODO Use map instead of vector

    public:
        GameObject();

        ~GameObject();

        template<typename T>
        Component *AddComponent() {
            auto newComp = mComponents.emplace_back(std::make_unique<T>()).get();
            newComp->Register(); //Run register func (if overloaded)
            return newComp;
        };

        template<typename T>
        Component *GetComponent() {
            for (const auto &component : mComponents) {
                if (dynamic_cast<T *>(component.get()) != nullptr)
                    return component.get();
            }
        };

        template<typename T>
        Component *FindComponent() {
            for (const auto &component : mComponents) {
                if (dynamic_cast<T *>(component.get()) != nullptr)
                    return component.get();
            }
        };

        template<typename T>
        bool RemoveComponent() {
            for (const auto &component : mComponents) {
                if (dynamic_cast<T *>(component.get()) != nullptr) {
                    mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), component),
                                      mComponents.end());
                    return true;
                }
            }

            return false; //There was no component of that type on the object
        };

        void Update();

        std::string ToString();

        void GenerateFromData(std::vector<std::string> data);
    };

}

#endif //HWENGINE_GAMEOBJECT_H
