//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <vector>
#include "Window.h"
#include <vulkan/vulkan.h>
#include "../Entity/Components/Renderer.h"
#include "../../../Libraries/GLFW/include/GLFW/glfw3.h"
#include "GUI/GUISystem.h"

namespace TandenEngine {

    class RenderingSystem {
    private:

        static VkInstance VulkanInstance;

        static std::vector<Renderer *> mRenderers;

        static Window* testWindow;

        static void InitGLFW();
        static void InitVulkan();
        static void InitWindow(int windowWidth, int windowHeight, std::string windowName);
        static void PollWindowEvents();

    public:
        static void Draw();

        static void RegisterRenderer(Renderer *newRenderer);

        static void InitSystem();

        static void Cleanup();

    };

}

#endif //RENDERINGSYSTEM_H
