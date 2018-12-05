//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef HWENGINE_COMPONENT_H
#define HWENGINE_COMPONENT_H

#include <string>
#include <vector>

namespace TandenEngine {

    enum ComponentType
    {
        TRANSFORM = 0,
        MESHFILTER = 1,
        MESHRENDERER = 2,
        PHYSICSCOMPONENT = 3,
        RENDERER = 4,
        SPRITERENDERER = 5,
        COLLIDER = 6
    };

    class Component {
    public:
        ComponentType mType;
        virtual void Update()=0; //Base update function for all components

        virtual void Register() {}; //Registering function some special components have (see renderer and physics component)

        virtual std::string ToString(); //Conversion function to go from the component to a serializable string

        virtual std::unique_ptr<Component> Clone()=0;

        virtual Component* ConvertFromString(std::vector<std::string> input)=0;
    };


}

#endif //HWENGINE_COMPONENT_H
