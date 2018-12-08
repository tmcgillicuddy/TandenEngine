//
// Created by thomas.mcgillicuddy on 10/31/2018.
// lots of help from vulkan-tutorial.com because I am still learning to set up a vulkan renderer in the first place -Rosser
//

#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <vector>
#include <set>
#include <algorithm>
#include "Window.h"
#include <vulkan/vulkan.h>
#include "../Entity/Components/Renderer.h"
#include "../../../Libraries/GLFW/include/GLFW/glfw3.h"
#include <optional>
#include "GLFW/glfw3.h"
#include "GUI/GUISystem.h"

const int windowWidth = 800;
const int windowHeight = 600;

namespace TandenEngine {

    //struct to check if graphics card supports necessary Vulkan queue families
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    //to check if the device can handle the following
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;              //max width and height of images
        std::vector<VkSurfaceFormatKHR> formats;            //color space and pixel formatting
        std::vector<VkPresentModeKHR> presentModes;         //presentation modes
    };

    //vector of required extensions, add if you need!
    const std::vector<const char*> DeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };



    class RenderingSystem {
    private:

        static VkInstance VulkanInstance;                   //vulkan instance
        static VkPhysicalDevice physicalDevice;             //our graphics card
        static VkDevice logicalDevice;                      //logical interface with graphics card
        static VkQueue gfxQueue;                            //graphics queue for graphics events
        static VkSurfaceKHR WindowSurface;                  //surface of window
        static VkQueue presentationQueue;
        static VkSwapchainKHR swapChain;                    //the infamous SWAP CHAIN
        static VkFormat swapChainImageFormat;
        static std::vector<VkImage> swapChainImages;
        static std::vector<VkImageView> swapChainImageViews;
        static VkExtent2D swapChainExtent;

        static std::vector<Renderer *> mRenderers;          //vector of renderers
        static Window* testWindow;                          //window instance (just one for now)


        //init
        static void InitGLFW();
        static void InitVulkan();

        //InitVulkan comprised of
            static void InitVKInstance();                                                                //creating instance

            static void SelectPhysicalDevice();                                                          //polling and selecting a graphics card to use
            static bool SuitableDevice(VkPhysicalDevice targetDevice);                                   //checking if a graphics card is suitable
            static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice targetDevice);                  //checking queue families of graphics card so VK can send events through it
            static bool CheckDeviceExtSupport(VkPhysicalDevice targetDevice);                            //check if device has all required extensions from vector of listed requirements
            static void InitWindowSurface();                                                             //creating surface for window instance
            static void InitLogicalDevice();                                                             //initialize logical device to interact with graphics card

            static SwapChainSupportDetails PollSwapChainSupport(VkPhysicalDevice targetDevice);    //poll device for its swapchain properties
            static VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
            static VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
            static VkExtent2D RenderingSystem::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
            static void CreateSwapChain();
            static void CreateImageViews();


        static void InitWindow(int windowWidth, int windowHeight, std::string windowName);               // init window instance
        static void PollWindowEvents();                                                                  //maintain during engine runs

    public:
        static void Draw();

        static void RegisterRenderer(Renderer *newRenderer);


        static void InitSystem();

        static void Cleanup();

    };

}

#endif //RENDERINGSYSTEM_H
