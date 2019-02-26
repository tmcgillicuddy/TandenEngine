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
        float data[3] = {
               mTransformLocal.r1.x,
               mTransformLocal.r1.y,
               mTransformLocal.r1.z
        };
        ImGui::InputFloat3("Position", data);
        ImGui::Separator();
    }

}