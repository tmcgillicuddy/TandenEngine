//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_AUDIOSOURCE_H
#define TANDENENGINE_AUDIOSOURCE_H

#include "../Component.h"

namespace TandenEngine {

    class AudioSource : public Component {
    public:
        AudioSource();
        ~AudioSource();

        //Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output a mesh collider object
    };
}

#endif //TANDENENGINE_AUDIOSOURCE_H
