//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_MESHCOLLIDER_H
#define TANDENENGINE_MESHCOLLIDER_H

#include "Collider.h"

namespace TandenEngine {

    class MeshCollider : public Collider {
     public:
        MeshCollider();

        // Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a mesh collider object
        Component * ConvertFromString(std::vector<std::string> input) override;

        // Collider Overrides
        void GenGUI() override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_MESHCOLLIDER_H
