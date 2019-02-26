//
// Created by thomas.mcgillicuddy on 12/5/2018.
//

#ifndef TANDENENGINE_CAMERA_H
#define TANDENENGINE_CAMERA_H

#include "../Component.h"

namespace TandenEngine {
    class Camera : public Component {
     public:
        float mFOV = 60;  // Field of View
        float mNearClipDist = 1;  // Near clipping plane distance
        float mFarClipDist = 100;  // Far clipping plane distance
        vec4 mClearColor = vec4(1,1,1,1);
        Camera();

        // Component Overrides
        void Update() override;
        std::unique_ptr<Component> Clone() override;
        std::string ToString() override;
        // Takes in some string data and will output a camera object
        Component * ConvertFromString(std::vector<std::string> input) override;

        // Call Raytrace on this camera
        void RayTraceThisCam();

        void GenGUI() override;
    };
}  // namespace TandenEngine

#endif  // TANDENENGINE_CAMERA_H
