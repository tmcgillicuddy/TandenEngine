//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_AUDIOLISTENER_H
#define TANDENENGINE_AUDIOLISTENER_H

#include "../Component.h"

namespace TandenEngine {
    class AudioListener : public Component {
    public:
        AudioListener();

        //Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        Component * ConvertFromString(std::vector<std::string> input) override; //Takes in some string data and will output an audio listener object
    };
}

#endif //TANDENENGINE_AUDIOLISTENER_H
