//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "../../Entity/Components/ComponentHeader.h"
#include <imgui.h>

namespace TandenEngine {

    void Component::GenGUI() {
        ImGui::TextColored(ImVec4(1,0,0,1), "GENGUI NOT IMPLEMENTED");
    }

    void Transform::GenGUI() {
        ImGui::Text("Transform");
        float posData[3] = {
               mTransformLocal.r1.x,
               mTransformLocal.r1.y,
               mTransformLocal.r1.z
        };
        float rotData[3] = {
                mTransformLocal.r2.x,
                mTransformLocal.r2.y,
                mTransformLocal.r2.z
        };
        float scaleData[3] = {
                mTransformLocal.r3.x,
                mTransformLocal.r3.y,
                mTransformLocal.r3.z
        };
        ImGui::InputFloat3("Position", posData);
        ImGui::InputFloat3("Rotation", rotData);
        ImGui::InputFloat3("Scale", scaleData);

    }

}