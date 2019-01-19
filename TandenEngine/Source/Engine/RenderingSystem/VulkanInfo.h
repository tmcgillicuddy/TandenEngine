//
// Created by thomas.mcgillicuddy on 1/19/2019.
//

#ifndef TANDENENGINE_VULKANINFO_H
#define TANDENENGINE_VULKANINFO_H

#include <set>
#include <fstream>
#include <vector>
#include <optional>
#include <vulkan/vulkan.h>
#include "GLFW/glfw3.h"

#include "RenderingSystem.h"

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
        //TODO make pointers to allow initialization without allocation
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

}


#endif //TANDENENGINE_VULKANINFO_H
