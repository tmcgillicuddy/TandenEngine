//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Transform.h"
#include "../../Serialization/Serializer.h"

namespace TandenEngine {

    Transform::Transform() {
        mType = ComponentType::TRANSFORM;
    }

    Transform::~Transform() {
    }

    void Transform::Update() {
        std::cout << "Updating Transform \n";
    }

    std::string Transform::ToString() {
        std::string data = Component::ToString(); //Call the base to string function
        //Add component specific attributes
        data += "Pos: " + std::to_string(position.x) + " " + std::to_string(position.y) + " " + std::to_string(position.z) + '\n';
        data += "Rot: " + std::to_string(rotation.x) + " " + std::to_string(rotation.y) + " " + std::to_string(rotation.z)+ '\n';
        data += "Scale: " + std::to_string(scale.x) + " " + std::to_string(scale.y) + " " + std::to_string(scale.z)+ '\n';
        return data;
    }

    Component * Transform::ConvertFromString(std::vector<std::string> data) {
        Transform * newComp = new Transform();
        newComp->position = Vector3(std::stof(data.at(2)),std::stof(data.at(3)),std::stof(data.at(4)));
        newComp->rotation = Vector3(std::stof(data.at(6)),std::stof(data.at(7)),std::stof(data.at(8)));
        newComp->scale = Vector3(std::stof(data.at(10)),std::stof(data.at(11)),std::stof(data.at(12)));
        std::cout << newComp->position;
        return newComp;
    }

    std::unique_ptr <Component> Transform::Clone() {
        return std::unique_ptr<Transform>(this);
    }

}                                                                                                                                                               