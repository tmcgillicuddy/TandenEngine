//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "ParticleSystem.h"

namespace TandenEngine
{
    ParticleSystem::ParticleSystem() {
    }

    void ParticleSystem::Update() {

    }

    std::unique_ptr<Component> ParticleSystem::Clone() {
        return std::unique_ptr<ParticleSystem>(this);
    }

    std::string ParticleSystem::ToString() {
        return PhysicsComponent::ToString();
    }

    Component *ParticleSystem::ConvertFromString(std::vector<std::string> input) {
        return PhysicsComponent::ConvertFromString(input);
    }
}