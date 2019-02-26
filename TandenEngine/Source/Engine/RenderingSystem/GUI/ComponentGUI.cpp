//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "../../Entity/Components/ComponentHeader.h"
#include <imgui.h>

namespace TandenEngine {

    void Component::GenGUI() {
        ImGui::TextColored(ImVec4(1,0,0,1), "GENGUI NOT IMPLEMENTED");
    }

    void Camera::GenGUI() {
        ImGui::Text("Camera");
        ImGui::SliderFloat("FOV", &mFOV, 0, 90);
        ImGui::InputFloat("Near Clip Dist", &mNearClipDist);
        ImGui::InputFloat("Far Clip Dist", &mFarClipDist);
        ImGui::ColorEdit4("Clear Color", mClearColor.v);
    }

    void Transform::GenGUI() {
        ImGui::Text("Transform");
        ImGui::InputFloat3("Position", mTransformLocal.r1.v);
        ImGui::InputFloat3("Rotation", mTransformLocal.r2.v);
        ImGui::InputFloat3("Scale", mTransformLocal.r3.v);

    }

}