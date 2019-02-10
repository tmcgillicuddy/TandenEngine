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
        // TODO(Nils) update local and ws transforms data based on parent
        // TODO(Nils) update the relative vector macros (forward, right, up)
    }

    void Transform::SetParent(Transform *target) {
        mParent = target;
        target->AddChild(this);
        Update();  // Call update once to update relative info
    }

    void Transform::AddChild(Transform *target) {
        mChildren.push_back(target);
    }

    void Transform::RemoveChild(Transform *target) {
        auto it = std::find(mChildren.begin(), mChildren.end(), target);
        if (it != mChildren.end()) { mChildren.erase(it); }
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
}   // namespace TandenEngine
