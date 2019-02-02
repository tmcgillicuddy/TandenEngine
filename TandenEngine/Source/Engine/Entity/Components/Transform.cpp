//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include <algorithm>

#include "Transform.h"
#include "../../Serialization/Serializer.h"

namespace TandenEngine {

    Transform::Transform() {
        mType = ComponentType::TRANSFORM;
    }

    Transform::~Transform() {
    }

    void Transform::Update() {
        //TODO multiply local transform by parent transform
        //std::cout << "Updating Transform \n";
    }

    std::string Transform::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        data += "Pos: " + std::to_string(mTransformData.r1.x) + " " + std::to_string(mTransformData.r1.y) + " " + std::to_string(mTransformData.r1.z) + '\n';
        data += "Rot: " + std::to_string(mTransformData.r2.x) + " " + std::to_string(mTransformData.r2.y) + " " + std::to_string(mTransformData.r2.z)+ '\n';
        data += "Scale: " + std::to_string(mTransformData.r3.x) + " " + std::to_string(mTransformData.r3.y) + " " + std::to_string(mTransformData.r3.z)+ '\n';
        return data;
    }

    Component * Transform::ConvertFromString(std::vector<std::string> data) {
        Transform * newComp = new Transform();
        newComp->mTransformData.r1 = vec3(std::stof(data.at(2)),std::stof(data.at(3)),std::stof(data.at(4)));
        newComp->mTransformData.r2 = vec3(std::stof(data.at(6)),std::stof(data.at(7)),std::stof(data.at(8)));
        newComp->mTransformData.r3 = vec3(std::stof(data.at(10)),std::stof(data.at(11)),std::stof(data.at(12)));
        std::cout << newComp->mTransformData.r1;
        return newComp;
    }

    std::unique_ptr <Component> Transform::Clone() {
        return std::unique_ptr<Transform>(this);
    }

    void Transform::Translate(vec3 dir) {
        mTransformData.r1 += dir;
    }

    void Transform::LookAt(Transform *target) {
    }

    void Transform::Rotate(vec3 euler) {
    }

    void Transform::SetParent(Transform *target) {
        mParent = target;
        mParent->mChildren.push_back(this);
    }

    void Transform::AddChild(Transform *target) {
        target->mParent = this;
        mChildren.push_back(target);
    }

    void Transform::RemoveChild(Transform *target) {
        mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), target), mChildren.end());
    }
}                                                                                                                                                               