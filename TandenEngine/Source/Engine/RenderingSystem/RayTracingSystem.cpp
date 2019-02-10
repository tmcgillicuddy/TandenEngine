//
// Created by thomas.mcgillicuddy on 2/10/2019.
//

#include "RayTracingSystem.h"

namespace TandenEngine {
    void RayTracingSystem::RayTraceToTexture(Camera targetCam, int width, int height) {
        // Create texture buffer

        for (int x=0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                // Create Ray

                // Fire Ray

                // If hit set pixel to integrated material info

                // If not hit, set pixel to skybox

            }
        }

        // Apply texture

        // Output texture
    }
}