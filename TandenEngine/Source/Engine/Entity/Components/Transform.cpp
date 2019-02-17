#include "Transform.h"

namespace TandenEngine {

    Transform::Transform() {
        mType = ComponentType::TRANSFORM;
    }

    void Transform::Translate(vec3 dir) {
    }

    void Transform::LookAt(Transform *target) {
    }

    void Transform::Rotate(vec3 euler) {
    }

    void Transform::Update() {
        mTransformGlobal = mParent->mTransformGlobal + mTransformLocal;
        // TODO(Nils) update the relative vector macros (forward, right, up)
    }

    void Transform::SetParent(Transform *target) {
        mParent = target;
        target->AddChild(this);
        Update();  // Call update once to update relative info
    }

    void Transform::AddChild(Transform *target) {
        mChildren.push_back(target);
    }

    void Transform::RemoveChild(Transform *target) {
        auto it = std::find(mChildren.begin(), mChildren.end(), target);
        if (it != mChildren.end()) { mChildren.erase(it); }
    }

    std::string Transform::ToString() {
        std::string data = Component::ToString();  // Call the base to string function
        // Add component specific attributes
        data += "Local Pos: " + std::to_string(mTransformLocal.r1.x) +
                " " + std::to_string(mTransformLocal.r1.y) +
                " " + std::to_string(mTransformLocal.r1.z) + '\n';

        data += "Local Rot: " + std::to_string(mTransformLocal.r2.x) +
                " " + std::to_string(mTransformLocal.r2.y) +
                " " + std::to_string(mTransformLocal.r2.z)+ '\n';

        data += "Local Scale: " + std::to_string(mTransformLocal.r3.x) +
                " " + std::to_string(mTransformLocal.r3.y) +
                " " + std::to_string(mTransformLocal.r3.z)+ '\n';

        data += "Global Pos: " + std::to_string(mTransformGlobal.r1.x) +
                " " + std::to_string(mTransformGlobal.r1.y) +
                " " + std::to_string(mTransformGlobal.r1.z) + '\n';

        data += "Global Rot: " + std::to_string(mTransformGlobal.r2.x) +
                " " + std::to_string(mTransformGlobal.r2.y) +
                " " + std::to_string(mTransformGlobal.r2.z)+ '\n';

        data += "Global Scale: " + std::to_string(mTransformGlobal.r3.x) +
                " " + std::to_string(mTransformGlobal.r3.y) +
                " " + std::to_string(mTransformGlobal.r3.z)+ '\n';
        return data;
    }

    Component * Transform::ConvertFromString(std::vector<std::string> data) {
        Transform * newComp = new Transform();
        newComp->mTransformLocal.r1 =
                vec3(std::stof(data.at(2)), std::stof(data.at(3)), std::stof(data.at(4)));

        newComp->mTransformLocal.r2 =
                vec3(std::stof(data.at(6)), std::stof(data.at(7)), std::stof(data.at(8)));

        newComp->mTransformLocal.r3 =
                vec3(std::stof(data.at(10)), std::stof(data.at(11)), std::stof(data.at(12)));

        return newComp;
    }

    std::unique_ptr<Component> Transform::Clone() {
       return std::unique_ptr<Transform>();
    }
}   // namespace TandenEngine
