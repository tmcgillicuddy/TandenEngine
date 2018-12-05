//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "AudioClip.h"

TandenEngine::AudioClip::AudioClip():Resource(ResourceType::AUDIO) {

}

bool TandenEngine::AudioClip::CheckIfSupported(std::string extension) {
    return (extension == ".wav" || extension == ".mp3");
}

namespace TandenEngine {

    AudioClip::AudioClip() {
        mResourceType = ResourceType::AUDIO;
    }

    bool AudioClip::CheckIfSupported(std::string extension) {
        return (extension == ".wav" || extension == ".mp3");
    }

}
