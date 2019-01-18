//
// Created by thomas.mcgillicuddy on 12/4/2018.
//

#include "LightComponent.h"
#include "../../../RenderingSystem/RenderingSystem.h"
namespace TandenEngine
{

    void LightComponent::Update() {
    }

    void LightComponent::Register() {
    }

    std::unique_ptr<Component> LightComponent::Clone() {
        return std::unique_ptr<LightComponent>(this);
    }

    std::string LightComponent::ToString() {
        return Component::ToString();
    }

    Component *LightComponent::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}