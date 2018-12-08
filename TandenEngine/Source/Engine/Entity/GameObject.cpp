//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "GameObject.h"
#include "Components/ComponentHeader.h"

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
                SelectComponenet(type, endData);
            }
        }
    }

    void GameObject::SelectComponenet(ComponentType type, std::vector<std::string> endData) {
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
                newComp = new MeshRenderer();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::SPRITERENDERER:
                newComp = new SpriteRenderer();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::PHYSICSCOMPONENT:
                newComp = new MeshRenderer();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::RENDERER:
                newComp = new MeshRenderer();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::BOXCOLLIDER:
                newComp = new BoxCollider();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::SPHERECOLLIDER:
                newComp = new SphereCollider();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::MESHCOLLIDER:
                newComp = new MeshCollider();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::CAPSULECOLLIDER:
                newComp = new CapsuleCollider();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::AUDIOLISTENER:
                newComp = new AudioListener();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::AUDIOSOURCE:
                newComp = new AudioSource();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::PARTICLESYSTEM:
                newComp = new ParticleSystem();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::RIGIDBODY:
                newComp = new RigidBody();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::CAMERA:
                newComp = new Camera();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::LIGHTCOMPONENT:
                newComp = new LightComponent();
                newComp->ConvertFromString(endData);
                break;
        }
        if (newComp != nullptr) {
            mComponents.emplace_back(newComp);
        }
    }

}