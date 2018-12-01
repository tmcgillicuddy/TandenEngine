//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "GameObject.h"
#include "./Components/Transform.h"

namespace TandenEngine {

    GameObject::GameObject() {
        AddComponent<Transform>();
    }

    GameObject::~GameObject() {

    }

    void GameObject::Update() { //Run each component's update function
        std::cout << "Updating GameObject \n";
        for (const auto &component : mComponents) {
            if (component.get() != nullptr)
                component->Update();
        }
    }

    std::string GameObject::ToString() {
        std::string data = mName + "\n";
        for (const auto &component : mComponents)
        {
            data += component->ToString();
            data += "---\n";
        }
        return data;
    }

}