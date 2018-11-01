//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_COMPONENT_H
#define HWENGINE_COMPONENT_H

namespace TandenEngine {

    class Component {
    public:
        virtual void Update() {};

        virtual void Register() {};
    };

}

#endif //HWENGINE_COMPONENT_H
