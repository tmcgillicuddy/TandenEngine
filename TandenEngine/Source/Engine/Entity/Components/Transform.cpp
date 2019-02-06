#include "Transform.h"

namespace TandenEngine {

    Transform::Transform() {
    }

    void Transform::Translate(vec3 dir) {
    }

    void Transform::LookAt(Transform *target) {
    }

    void Transform::Rotate(vec3 euler) {
    }

    void Transform::Update() {
    }

    void Transform::SetParent(Transform *target) {
    }

    void Transform::AddChild(Transform *target) {
    }

    void Transform::RemoveChild(Transform *target) {
    }

    std::string Transform::ToString() {
        return "";
    }

    Component *Transform::ConvertFromString(std::vector<std::string> input) {
        return nullptr;
    }

    std::unique_ptr<Component> Transform::Clone() {
        return std::unique_ptr<Transform>();
    }
}  // namespace TandenEngine

