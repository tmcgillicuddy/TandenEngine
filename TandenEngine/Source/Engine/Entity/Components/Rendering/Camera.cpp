//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#include "Camera.h"
#include "../../../RenderingSystem/RayTracingSystem.h"

namespace TandenEngine {

    Camera::Camera() {
    }

    void Camera::Update() {
    }

    std::unique_ptr<Component> Camera::Clone() {
        return std::unique_ptr<Camera>(this);
    }

    std::string Camera::ToString() {
        return Component::ToString();
    }

    Component *Camera::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }

    void Camera::RayTraceThisCam() {
        // TODO(Anyone) Use an input width and height
        RayTracingSystem::RayTraceToTexture(*this, 1920, 1080);
    }
}  // namespace TandenEngine
