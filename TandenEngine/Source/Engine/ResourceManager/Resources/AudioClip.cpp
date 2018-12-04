//
// Created by thomas.mcgillicuddy on 11/3/2018.
//

#include "AudioClip.h"

namespace TandenEngine {

    AudioClip::AudioClip() {
        mResourceType = ResourceType::AUDIO;
    }

    bool AudioClip::CheckIfSupported(std::string extension) {
        return (extension == ".wav" || extension == ".mp3");
    }

}