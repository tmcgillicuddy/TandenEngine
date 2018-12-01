//
// Created by thomas.mcgillicuddy on 10/21/2018.
//

#include "Transform.h"
#include "../../Serialization/Serializer.h"

namespace TandenEngine {

    Transform::Transform() {

    }

    Transform::~Transform() {

    }

    void Transform::Update() {
        std::cout << "Updating Transform \n";

    }

    std::string Transform::ToString() {
        std::string data = "Transform\n";
        data += "Pos: " + std::to_string(position.x) + " " + std::to_string(position.y) + " " + std::to_string(position.z) + '\n';
        data += "Rot: " + std::to_string(rotation.x) + " " + std::to_string(rotation.y) + " " + std::to_string(rotation.z)+ '\n';
        data += "Scale: " + std::to_string(scale.x) + " " + std::to_string(scale.y) + " " + std::to_string(scale.z)+ '\n';
        return data;
    }

    Component * Transform::ConvertFromString(std::string data) {
        Transform * newComp = new Transform();
        float x,y,z;

        std::vector<std::string> dataOutput = Serializer::SeperateString(data);

        for(auto word: dataOutput)
        {
            std::cout<<word <<std::endl;
        }

        return newComp;
    }

    std::unique_ptr <Component> Transform::Clone() {
        return std::unique_ptr<Transform>(this);
    }

}