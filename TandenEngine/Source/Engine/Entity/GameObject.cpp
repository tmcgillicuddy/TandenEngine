//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "GameObject.h"
#include "Components/ComponentHeader.h"

namespace TandenEngine {

    GameObject::GameObject() {
        mTransform = dynamic_cast<Transform*>(AddComponent<Transform>());
    }

    GameObject::~GameObject() {
    }

    void GameObject::Update() { //Run each component's update function
        //std::cout << "Updating GameObject \n";
        for (auto &pair : mComponents) {
           pair.second->Update();
        }
    }

    std::string GameObject::ToString() {
        std::string data = mName + "\n";
        for (auto &pair : mComponents)
        {
            data += pair.second->ToString();
            data += "---\n";
        }
        return data;
    }

    void GameObject::GenerateFromData(std::vector<std::string> data) {
        mName = data[0];  // First string is always the name
        // Run through every component in the gameobject and generate a new component for it
        for (size_t i=1; i < data.size(); ++i) {
            //Get component data
            if (data[i] != "-----") {
                std::vector<std::string> endData;
                endData.emplace_back(data[i]);
                ComponentType type = (ComponentType) std::stoi(data[i]);
                ++i;
                while (i < data.size() && data[i] != "---") {  // Until the end of this object
                    endData.emplace_back(data[i]);  // Add it to the object
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
                newComp = (mComponents[typeid(Transform)]
                        = std::make_unique<Transform>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::MESHRENDERER:
                newComp = (mComponents[typeid(MeshRenderer)]
                        = std::make_unique<MeshRenderer>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::MESHFILTER:
                newComp = (mComponents[typeid(MeshFilter)]
                        = std::make_unique<MeshFilter>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::SPRITERENDERER:
                newComp = (mComponents[typeid(SpriteRenderer)]
                        = std::make_unique<SpriteRenderer>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::BOXCOLLIDER:
                newComp = (mComponents[typeid(BoxCollider)]
                        = std::make_unique<BoxCollider>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::SPHERECOLLIDER:
                newComp = (mComponents[typeid(SphereCollider)]
                        = std::make_unique<SphereCollider>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::MESHCOLLIDER:
                newComp = (mComponents[typeid(MeshCollider)]
                        = std::make_unique<MeshCollider>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::CAPSULECOLLIDER:
                newComp = (mComponents[typeid(CapsuleCollider)]
                        = std::make_unique<CapsuleCollider>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::AUDIOLISTENER:
                newComp = (mComponents[typeid(AudioListener)]
                        = std::make_unique<AudioListener>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::AUDIOSOURCE:
                newComp = (mComponents[typeid(AudioSource)]
                        = std::make_unique<AudioSource>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::PARTICLESYSTEM:
                newComp = (mComponents[typeid(ParticleSystem)]
                        = std::make_unique<ParticleSystem>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::RIGIDBODY:
                newComp = (mComponents[typeid(RigidBody)]
                        = std::make_unique<RigidBody>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::CAMERA:
                newComp = (mComponents[typeid(Camera)]
                        = std::make_unique<Camera>()).get();
                newComp->ConvertFromString(endData);
                break;
            case ComponentType::LIGHTCOMPONENT:
                newComp = (mComponents[typeid(LightComponent)]
                        = std::make_unique<LightComponent>()).get();
                newComp->ConvertFromString(endData);
                break;
        }
        if (newComp != nullptr) {
            newComp->Register();  // Run register func (if overloaded)
            newComp->SetBaseComponent(this);
        }
    }

}  // namespace TandenEngine
