//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "../../Entity/GameObject.h"
#include "../../Entity/Components/ComponentHeader.h"
#include <imgui.h>

namespace TandenEngine {

    void Component::GenGUI() {
        ImGui::TextColored(ImVec4(1,0,0,1), "GENGUI NOT IMPLEMENTED");
    }

    void MaterialComp::GenGUI() {
        bool open = ImGui::TreeNode("Material");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
                mParentObject->RemoveComponent<MaterialComp>();
            ImGui::EndPopup();
        }
        if(open) {
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
        bool open = ImGui::TreeNode("Audio Source");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
                mParentObject->RemoveComponent<AudioSource>();
            ImGui::EndPopup();
        }
        if(open) {
            //TODO(Thomas) add vars
            ImGui::TreePop();
        }
    }

    void BoxCollider::GenGUI() {
        bool open = ImGui::TreeNode("Box Collider");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
                mParentObject->RemoveComponent<BoxCollider>();
            ImGui::EndPopup();
        }
        if(open) {
            //TODO(Thomas) add vars
            ImGui::TreePop();
        }
    }

    void SphereCollider::GenGUI() {
        bool open = ImGui::TreeNode("Sphere Collider");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
                mParentObject->RemoveComponent<SphereCollider>();
            ImGui::EndPopup();
        }
        if(open) {
            ImGui::InputFloat("Radius", &mRadius);
            ImGui::TreePop();
        }
    }

    void RigidBody::GenGUI()
    {
        bool open = ImGui::TreeNode("Rigidbody");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
                mParentObject->RemoveComponent<RigidBody>();
            ImGui::EndPopup();
        }
        if(open) {
            ImGui::Checkbox("Static", &mStatic);
            ImGui::InputFloat("Mass", &mMass);
            ImGui::InputFloat("Friction", &mFriction);
            ImGui::TreePop();
        }
    }

    void Camera::GenGUI() {
        bool open = ImGui::TreeNode("Camera");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
            {
                mParentObject->RemoveComponent<Camera>();
            }
            ImGui::EndPopup();
        }
        if(open) {
            ImGui::SliderFloat("FOV", &mFOV, 0, 90);
            ImGui::InputFloat("Near Clip Dist", &mNearClipDist);
            ImGui::InputFloat("Far Clip Dist", &mFarClipDist);
            ImGui::ColorEdit4("Clear Color", mClearColor.v);
            ImGui::TreePop();
        }
    }

    void Transform::GenGUI() {
        bool open = ImGui::TreeNode("Transform");
        if(ImGui::BeginPopupContextItem())
        {
            if (ImGui::Selectable("Remove Component"))
                mParentObject->RemoveComponent<Transform>();
            ImGui::EndPopup();
        }
        if(open) {
            ImGui::InputFloat3("Position", mTransformLocal.r1.v);
            ImGui::InputFloat3("Rotation", mTransformLocal.r2.v);
            ImGui::InputFloat3("Scale", mTransformLocal.r3.v);
            ImGui::TreePop();
        }
    }

}