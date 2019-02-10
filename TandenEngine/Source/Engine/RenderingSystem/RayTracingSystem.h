//
// Created by thomas.mcgillicuddy on 2/10/2019.
//

#ifndef TANDENENGINE_RAYTRACINGSYSTEM_H
#define TANDENENGINE_RAYTRACINGSYSTEM_H

#include "../Entity/Components/Rendering/Camera.h"

namespace TandenEngine {

    class RayTracingSystem {
     public:
        // Ray Trace from the camera into the world
        static void RayTraceToTexture(Camera targetCam, int width, int height);
    };

}  // namespace TandenEngine

#endif  // TANDENENGINE_RAYTRACINGSYSTEM_H
