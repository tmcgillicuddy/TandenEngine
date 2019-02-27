//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef TANDENENGINE_COMPONENT_H
#define TANDENENGINE_COMPONENT_H

#include <string>
#include <vector>
#include "NilsMath.h"
#include <memory>

namespace TandenEngine {

    class GameObject;
    class Transform;

    enum ComponentType {
        TRANSFORM = 0,
        MESHFILTER = 1,
        MESHRENDERER = 2,
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
        LIGHTCOMPONENT = 15,
        MATERIALCOMP = 16
    };

    class Component {
     public:
        ComponentType mType;
        GameObject *mParentObject;
        Transform *mTransform;

        void SetBaseComponent(GameObject* gameObj);

        // Virtual/Abstract Functions
        virtual void Update() = 0;  // Base update function for all components
        // Base clone function for copying data from one gameobject to another (prefab generation)
        virtual std::unique_ptr<Component> Clone() = 0;
        // Registering function some special components have (see renderer and physics component)
        virtual void Register() {}
        // Conversion function to go from the component to a serializable string
        virtual std::string ToString();

        virtual Component* ConvertFromString(std::vector<std::string> input) = 0;

        virtual void GenGUI();
    };


}  // namespace TandenEngine

#endif  // TANDENENGINE_COMPONENT_H
