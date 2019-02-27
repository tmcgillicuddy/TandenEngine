#ifndef TANDENENGINE_GAMEOBJECT_H
#define TANDENENGINE_GAMEOBJECT_H

#include <unordered_map>
#include <typeindex>    // Provides typeindex so we can Type as a key in Map;
#include <utility>
#include <memory>
#include <algorithm>
#include <type_traits>  // Templates is_same

#include "Components/Component.h"

namespace TandenEngine {

    class GameObject {  // Game Objects always have at least a transform component
        friend class Prefab;
     public:
        std::string mName = "Test_Object";
        std::unordered_map<std::type_index, std::unique_ptr<Component>> mComponents;
        Transform * mTransform;  // The locally held pointer to transform comp

        GameObject();

        ~GameObject();

        template<typename T>
        Component *AddComponent() {
            auto newComp = (mComponents[typeid(T)] = std::make_unique<T>()).get();
            newComp->Register();  // Run register func (if overloaded)
            newComp->SetBaseComponent(this);
            return newComp;
        }

        template<typename T>
        Component *GetComponent() {
            if (mComponents.count(typeid(T)) != 0) {
                return mComponents[typeid(T)].get();
            }
            return nullptr;
        }

        template<typename T>
        bool RemoveComponent() {
            for (const auto &component : mComponents) {
                if (dynamic_cast<T *>(component.second.get()) != nullptr) {
                    mComponents.erase(std::remove(mComponents.begin(),
                            mComponents.end(), component), mComponents.end());
                    return true;
                }
            }

            return false;  // There was no component of that type on the object
        }

        void Update();

        std::string ToString();

        void GenerateFromData(std::vector<std::string> data);

        void SelectComponenet(ComponentType type, std::vector<std::string> data);

        std::string GetName() {return mName;}
        void SetName(std::string newName){mName = newName;}
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_GAMEOBJECT_H
