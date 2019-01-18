//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef TANDENENGINE_COMPONENT_H
#define TANDENENGINE_COMPONENT_H

#include <string>
#include <vector>


namespace TandenEngine {

    class GameObject;
    class Transform;

    enum ComponentType
    {
        TRANSFORM = 0,
        MESHFILTER = 1,
        MESHRENDERER = 2,
        PHYSICSCOMPONENT = 3,
        RENDERER = 4,

        SPRITERENDERER = 5,
        BOXCOLLIDER = 6,
        SPHERECOLLIDER = 7,
        MESHCOLLIDER = 8,
        CAPSULECOLLIDER = 9,
        AUDIOLISTENER = 10,
        AUDIOSOURCE = 11,
        PARTICLESYSTEM = 12,
        RIGIDBODY = 13,
        CAMERA = 14,
        LIGHTCOMPONENT = 15
    };

    class Component {
    public:
        ComponentType mType;
        GameObject *mParentObject;
        Transform *mTransform;

        void SetBaseComponent(GameObject* gameObj);

        //Virtual/Abstract Functions
        virtual void Update()=0; //Base update function for all components

        virtual std::unique_ptr<Component> Clone()=0; //Base clone function for copying data from one gameobject to another (prefab generation)

        virtual void Register() {}; //Registering function some special components have (see renderer and physics component)

        virtual std::string ToString(); //Conversion function to go from the component to a serializable string

        virtual Component* ConvertFromString(std::vector<std::string> input)=0;
    };


}

#endif //TANDENENGINE_COMPONENT_H
