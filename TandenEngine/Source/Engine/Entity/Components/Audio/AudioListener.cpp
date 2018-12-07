//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "AudioListener.h"

namespace TandenEngine
{

    AudioListener::AudioListener() {
    }

    void AudioListener::Update() {
    }

    std::unique_ptr<Component> AudioListener::Clone() {
        return std::unique_ptr<AudioListener>(this);
    }

    std::string AudioListener::ToString() {
        return Component::ToString();
    }

    Component *AudioListener::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}