//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "GameObject.h"
#include "Components/Transform.h"
#include "Components/Rendering/MeshRenderer.h"

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

    void GameObject::GenerateFromData(std::vector<std::string> data) {
        mName = data[0]; //First string is always the name
        for(auto i=1; i < data.size(); ++i) //Run through every component in the gameobject and generate a new component for it
        {
            //Get component data
            if(data[i] != "-----") {
                std::vector<std::string> endData;
                endData.emplace_back(data[i]);
                ComponentType type = (ComponentType) std::stoi(data[i]);
                ++i;
                while (i < data.size() && data[i] != "---") //Until the end of this object
                {
                    endData.emplace_back(data[i]); //Add it to the object
                    ++i;
                }
                //Make a new component
                Component *newComp = nullptr;
                switch (type) {
                    case ComponentType::TRANSFORM:
                        newComp = new Transform();
                        newComp->ConvertFromString(endData);
                        break;
                    case ComponentType::MESHRENDERER:
                        newComp = new MeshRenderer();
                        newComp->ConvertFromString(endData);
                        break;
                    case ComponentType::MESHFILTER:
                        newComp = new MeshRenderer(); //TODO Change
                        newComp->ConvertFromString(endData);
                        break;
                    case ComponentType::SPRITERENDERER:
                        newComp = new MeshRenderer(); //TODO Change
                        newComp->ConvertFromString(endData);
                        break;
                    case ComponentType::PHYSICSCOMPONENT:
                        newComp = new MeshRenderer(); //TODO Change
                        newComp->ConvertFromString(endData);
                        break;
                    case ComponentType::RENDERER:
                        newComp = new MeshRenderer(); //TODO Change
                        newComp->ConvertFromString(endData);
                        break;
                    case ComponentType::BOXCOLLIDER:
                        newComp = new MeshRenderer(); //TODO Change
                        newComp->ConvertFromString(endData);
                        break;
                }
                if (newComp != nullptr) {
                    mComponents.emplace_back(newComp);
                }
            }
        }
    }

}