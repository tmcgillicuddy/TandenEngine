//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "../../Entity/Components/ComponentHeader.h"
#include <imgui.h>

namespace TandenEngine {

    void Component::GenGUI() {
        ImGui::TextColored(ImVec4(1,0,0,1), "GENGUI NOT IMPLEMENTED");
    }

    void MaterialComp::GenGUI() {
        if(ImGui::TreeNode("Material")) {
            if(mAlbedo == nullptr) {
                ImGui::ColorEdit4("Albedo", mColor.v);
            } else {
                // TODO(Thomas) add file field
            }
            if(mMetallic == nullptr) {
                ImGui::SliderFloat("Metallic", &mMetallicVal, 0,1);
            } else {
                // TODO(Thomas) add file field
            }

            if(mRoughness == nullptr) {
                ImGui::SliderFloat("Roughness", &mRoughnessVal, 0,1);
            } else {
                // TODO(Thomas) add file field
            }
            ImGui::TreePop();
        }
    }

    void AudioSource::GenGUI() {
        if(ImGui::TreeNode("Audio Source")) {
            //TODO(Thomas) add vars
            ImGui::TreePop();
        }
    }

    void BoxCollider::GenGUI() {
        if(ImGui::TreeNode("Box Collider")) {
            //TODO(Thomas) add vars
            ImGui::TreePop();
        }
    }

    void SphereCollider::GenGUI() {
        if(ImGui::TreeNode("Sphere Collider")) {
            ImGui::InputFloat("Radius", &mRadius);
            ImGui::TreePop();
        }
    }

    void RigidBody::GenGUI() {
        if(ImGui::TreeNode("Rigidbody")) {
            ImGui::Checkbox("Static", &mStatic);
            ImGui::InputFloat("Mass", &mMass);
            ImGui::InputFloat("Friction", &mFriction);
            ImGui::TreePop();
        }
    }

    void Camera::GenGUI() {
        if(ImGui::TreeNode("Camera")) {
            ImGui::SliderFloat("FOV", &mFOV, 0, 90);
            ImGui::InputFloat("Near Clip Dist", &mNearClipDist);
            ImGui::InputFloat("Far Clip Dist", &mFarClipDist);
            ImGui::ColorEdit4("Clear Color", mClearColor.v);
            ImGui::TreePop();
        }
    }

    void Transform::GenGUI() {
        if(ImGui::TreeNode("Transform")) {
            ImGui::InputFloat3("Position", mTransformLocal.r1.v);
            ImGui::InputFloat3("Rotation", mTransformLocal.r2.v);
            ImGui::InputFloat3("Scale", mTransformLocal.r3.v);
            ImGui::TreePop();
        }
    }

}