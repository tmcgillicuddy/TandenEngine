//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#ifndef TANDENENGINE_TRANSFORM_H
#define TANDENENGINE_TRANSFORM_H

#include <iostream>

#include "Component.h"
#include "NilsMath.h"

namespace TandenEngine {

    class Transform : public Component {
     public:
        mat3 mTransformLocal;
        mat3 mTransformGlobal;

        vec3 mForward;
        vec3 mRight;
        vec3 mUp;

        Transform * mParent = nullptr;
        std::vector<Transform*> mChildren;

        Transform();
        ~Transform() {}


        void Translate(vec3 dir);
        void SetPosition(vec3 pos);

        void LookAt(Transform * target);

        void Scale(vec3 scale);
        void SetScale(vec3 scale);

        void Rotate(vec3 euler);
        void SetRotation(vec3 euler);

        void Update() override;

        void SetParent(Transform * target);

        void AddChild(Transform * target);

        void RemoveChild(Transform * target);

        std::string ToString() override;

        // Takes in some string data and will output a transform object
        Component * ConvertFromString(std::vector<std::string> input) override;

        std::unique_ptr<Component> Clone() override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_TRANSFORM_H
