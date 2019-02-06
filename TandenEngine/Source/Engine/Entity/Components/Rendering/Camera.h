//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_CAMERA_H
#define TANDENENGINE_CAMERA_H

#include "../Component.h"

namespace TandenEngine {
    class Camera : public Component {
     public:
        Camera();

        // Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a mesh collider object
        Component * ConvertFromString(std::vector<std::string> input) override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_CAMERA_H
