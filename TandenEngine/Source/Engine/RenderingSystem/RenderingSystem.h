//
// Created by thomas.mcgillicuddy on 10/31/2018.
// lots of help from vulkan-tutorial.com because I am still learning to set up a vulkan renderer in the first place -Rosser
//

#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <vector>
#include "Window.h"
#include <vulkan/vulkan.h>
#include "../Entity/Components/Renderer.h"
#include "../../../Libraries/GLFW/include/GLFW/glfw3.h"
#include <optional>
#include "GLFW/glfw3.h"
#include "GUI/GUISystem.h"

namespace TandenEngine {

    //struct to check if graphics card can actually handle Vulkan queues
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() {return graphicsFamily.has_value();}
    };


    class RenderingSystem {
    private:

        static VkInstance VulkanInstance;                   //vulkan instance
        static VkPhysicalDevice physicalDevice;             //our graphics card
        static VkDevice logicalDevice;                      //logical interface with graphics card
        static VkQueue gfxQueue;                            //graphics queue for graphics events
        static VkSurfaceKHR windowSurface;                  //surface of window
        static std::vector<Renderer *> mRenderers;          //vector of renderers
        static Window* testWindow;                          //window instance (just one for now)

        //init
        static void InitGLFW();
        static void InitVulkan();

        //InitVulkan comprised of
            static void InitVKInstance();                                                       //creating instance

            static void SelectPhysicalDevice();                                                 //polling and selecting a graphics card to use
            static bool SuitableDevice(VkPhysicalDevice targetDevice);                          //checking if a graphics card is suitable
            static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);               //checking queue families of graphics card so VK can send events through it

            static void InitLogicalDevice();

        static void InitWindow(int windowWidth, int windowHeight, std::string windowName);      // init window instance

        static void PollWindowEvents();                                                         //maintain during engine runs

    public:
        static void Draw();

        static void RegisterRenderer(Renderer *newRenderer);


        static void InitSystem();

        static void Cleanup();

    };

}

#endif //RENDERINGSYSTEM_H
