//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "AudioSource.h"

namespace TandenEngine
{

    AudioSource::AudioSource() {
    }

    AudioSource::~AudioSource() {
    }

    void AudioSource::Update() {

    }

    std::unique_ptr<Component> AudioSource::Clone() {
        return std::unique_ptr<AudioSource>(this);
    }

    std::string AudioSource::ToString() {
        return Component::ToString();
    }

    Component *AudioSource::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }
}