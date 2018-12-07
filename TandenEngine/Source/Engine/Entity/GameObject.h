//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef TANDENENGINE_GAMEOBJECT_H
#define TANDENENGINE_GAMEOBJECT_H

//STD Classes
#include <vector>
#include <utility> //smart pointers
#include <memory>
#include <algorithm>
#include <iostream>

//Tanden Engine classes
#include "Components/Component.h"

namespace TandenEngine {

    class GameObject { //Game Objects always have at least a transform component
        friend class Prefab;
    private:
        std::string mName = "Test_Object";
        std::vector<std::unique_ptr<Component>> mComponents; //TODO Use map instead of vector

    public:
        GameObject();

        ~GameObject();

        template<typename T>
        Component *AddComponent() {
            auto newComp = mComponents.emplace_back(std::make_unique<T>()).get();
            newComp->Register(); //Run register func (if overloaded)
            newComp->SetBaseComponent(this);
            return newComp;
        };

        template<typename T>
        Component *GetComponent() {
            for (const auto &component : mComponents) {
                if (dynamic_cast<T *>(component.get()) != nullptr)
                    return component.get();
            }
            return nullptr;
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

        void SelectComponenet(ComponentType type, std::vector<std::string> data);
    };

}

#endif //TANDENENGINE_GAMEOBJECT_H
