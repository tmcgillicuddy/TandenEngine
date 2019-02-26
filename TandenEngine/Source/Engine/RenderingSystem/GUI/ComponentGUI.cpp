//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "../../Entity/Components/ComponentHeader.h

namespace TandenEngine {

    void Transform::GenGUI() {
        ImGui::Text("Transform");
        float data[3] = {
                comp->mTransformLocal.r1.x,
                comp->mTransformLocal.r1.y,
                comp->mTransformLocal.r1.z
        };
        ImGui::InputFloat3("Position", data);
        ImGui::Separator();
    }

}