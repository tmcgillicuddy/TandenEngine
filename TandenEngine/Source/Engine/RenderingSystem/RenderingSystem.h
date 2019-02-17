//
//  Created by thomas.mcgillicuddy on 10/31/2018.
//  lots of help from vulkan-tutorial.com because I am
//  still learning to set up a Vulkan renderer in the first place -Rosser
//

#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <iostream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include "GUI/GUISystem.h"

#include "Window.h"
#include "../Entity/Components/Rendering/Renderer.h"
#include "../Entity/Components/Rendering/Camera.h"
#include "VulkanInfo.h"

const int windowWidth = 800;  // TODO(Rosser) move these varibles to a base level source file
const int windowHeight = 600;

namespace TandenEngine {

    struct VulkanInfo;
    // TODO(Rosser) remove forward declaration once window dimensions vars are moved
    class RenderingSystem {
     private:
        static VulkanInfo mVulkanInfo;  // Wrapper for all vulkan specific varibles

        static std::vector<Renderer *> mRenderers;       // vector of renderers
        static Window* mWindow;                          // window instance (just one for now)

        static void InitGLFW();

        static void DrawWindow();

        static void InitWindow(int windowWidth, int windowHeight, std::string windowName);
        static void PollWindowEvents();

     public:
        static Camera * mMainCam;  // Main Camera
        static void Draw();

        static void RegisterRenderer(Renderer *newRenderer);
        // Accessor
        static const VulkanInfo * GetVulkanInfo();
        static Window * GetWindow();

        static void InitSystem();

        static void InitGraphicsPipeline();

        static void Cleanup();
    };

}  // namespace TandenEngine

#endif  // RENDERINGSYSTEM_H
