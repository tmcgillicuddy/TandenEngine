//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_COMPONENT_H
#define HWENGINE_COMPONENT_H

#include <string>

namespace TandenEngine {

    class Component {
    public:
        virtual void Update()=0;

        virtual void Register() {};

        virtual std::string ToString()=0;
    };

}

#endif //HWENGINE_COMPONENT_H
