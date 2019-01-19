//
// Created by thomas.mcgillicuddy on 10/31/2018.
// lots of help from vulkan-tutorial.com because I am still learning to set up a vulkan renderer in the first place -Rosser
//

#ifndef RENDERINGSYSTEM_H
#define RENDERINGSYSTEM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <optional>
#include <set>

#include "Window.h"
#include <vulkan/vulkan.h>
#include "../Entity/Components/Rendering/Renderer.h"
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

    struct VulkanInfo
    {
        //TODO make pointers to allow initilization without allocation
        VkInstance VulkanInstance;                   //vulkan instance
        VkPhysicalDevice physicalDevice;             //our graphics card
        VkDevice logicalDevice;                      //logical interface with graphics card
        VkQueue gfxQueue;                            //graphics queue for graphics events
        VkSurfaceKHR WindowSurface;                  //surface of window
        VkQueue presentationQueue;
        VkSwapchainKHR swapChain;                    //the infamous SWAP CHAIN
        VkFormat swapChainImageFormat;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        VkExtent2D swapChainExtent;
        VkPipelineLayout pipelineLayout;
        VkRenderPass renderPass;
        VkPipeline graphicsPipeline;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkSemaphore imageAvailableSemaphore;
        VkSemaphore renderFinishedSemaphore;

        //TODO Move vulkan init function headers here
        void InitVulkan();

    private:
        void InitVKInstance();                                                                //creating instance

        void SelectPhysicalDevice();                                                          //polling and selecting a graphics card to use
        bool SuitableDevice(VkPhysicalDevice targetDevice);                                   //checking if a graphics card is suitable
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice targetDevice);                  //checking queue families of graphics card so VK can send events through it
        bool CheckDeviceExtSupport(VkPhysicalDevice targetDevice);                            //check if device has all required extensions from vector of listed requirements
        void InitWindowSurface();                                                             //creating surface for window instance
        void InitLogicalDevice();                                                             //initialize logical device to interact with graphics card

        SwapChainSupportDetails PollSwapChainSupport(VkPhysicalDevice targetDevice);    //poll device for its swapchain properties
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void CreateSwapChain();
        void CreateImageViews();

        void CreateGraphicsPipeline();
        std::vector<char> ReadFile(const std::string& filename); //TODO Remove this
        VkShaderModule CreateShaderModule(const std::vector<char>& code); //TODO remove this, Used in Shader resource

        void CreateRenderPass();
        void CreateFramebuffers();
        void CreateCommandPool();
        void CreateCommandBuffers();
        void CreateSemaphores();         //used to synchronize when images are being presented
    };

    class RenderingSystem {
    private:
        static VulkanInfo mVulkanInfo; //Wrapper for all vulkan specific varibles

        static std::vector<Renderer *> mRenderers;          //vector of renderers
        static Window* mWindow;                          //window instance (just one for now)



        //init
        static void InitGLFW();

        static void DrawWindow();

        static void InitWindow(int windowWidth, int windowHeight, std::string windowName);               // init window instance
        static void PollWindowEvents();                                                                  //maintain during engine runs

    public:
        static void Draw();

        static void RegisterRenderer(Renderer *newRenderer);
        //Accessor
        static const VulkanInfo * GetVulkanInfo();
        static Window * GetWindow();

        static void InitSystem();

        static void Cleanup();

    };

}

#endif //RENDERINGSYSTEM_H
