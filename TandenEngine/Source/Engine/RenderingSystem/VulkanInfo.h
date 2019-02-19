//
//  Created by thomas.mcgillicuddy on 1/19/2019.
//

#ifndef TANDENENGINE_VULKANINFO_H
#define TANDENENGINE_VULKANINFO_H



#include <vulkan/vulkan.h>

#include <Windows.h>
#include <NilsMath.h>

#include <optional>

#include <array>
#include <set>
#include <fstream>
#include <vector>

#include "RenderingSystem.h"

#include "../ResourceManager/BufferManager/BufferManager.h"
#include "../ResourceManager/Resources/Model/Model.h"

#include "GLFW/glfw3.h"



namespace TandenEngine {


    // struct to check if graphics card supports necessary Vulkan queue families
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    // to check if the device can handle the following
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;              // max width and height of images
        std::vector<VkSurfaceFormatKHR> formats;            // color space and pixel formatting
        std::vector<VkPresentModeKHR> presentModes;         // presentation modes
    };

    // vector of required extensions, add if you need!
    const std::vector<const char*> DeviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    // validation layers for finding common errors
    const std::vector<const char*> ValidationLayers = {
            "VK_LAYER_LUNARG_standard_validation"
    };

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

    struct VulkanInfo {
        // TODO(Rosser) make pointers to allow initialization without allocation
        VkInstance VulkanInstance;                   // vulkan instance
        VkDebugUtilsMessengerEXT debugMessenger;     // debugs validation layers
        VkPhysicalDevice physicalDevice;             // our graphics card
        VkPhysicalDeviceMemoryProperties memoryProperties;
        VkDevice logicalDevice;                      // logical interface with graphics card
        VkQueue gfxQueue;                            // graphics queue for graphics events
        VkQueue presentationQueue;
        VkSurfaceKHR WindowSurface;                  // surface of window
        VkSwapchainKHR swapChain;                    // the infamous SWAP CHAIN
        VkFormat swapChainImageFormat;
        std::vector<VkImage> swapChainImages;
        std::vector<VkImageView> swapChainImageViews;
        VkExtent2D swapChainExtent;
        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        VkPipelineLayout pipelineLayout;
        VkRenderPass mRenderPass;
        VkPipeline graphicsPipeline;
        std::vector<VkFramebuffer> swapChainFramebuffers;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        VkAllocationCallbacks* mAllocator;
        size_t currentFrame = 0;
        const int maxFramesInFlight = 2;  // max concurrent frames to be processed
        bool framebufferResized = false;

        void InitVulkan();
        void InitVulkanPipeline();
        void RecreateSwapChain();
        void CleanupVulkan();

     private:
        void InitVKInstance();
        bool CheckValidationLayerSupport();

        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance,
                const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                const VkAllocationCallbacks* pAllocator,
                VkDebugUtilsMessengerEXT* pDebugMessenger);
        void SetupDebugMessenger();
        std::vector<const char*> GetRequiredExtensions();

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
                VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                void* pUserData);

        void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
        void SelectPhysicalDevice();
        bool SuitableDevice(VkPhysicalDevice targetDevice);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice targetDevice);
        bool CheckDeviceExtSupport(VkPhysicalDevice targetDevice);
        void InitWindowSurface();
        void InitLogicalDevice();

        SwapChainSupportDetails PollSwapChainSupport(VkPhysicalDevice targetDevice);

        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
                const std::vector<VkSurfaceFormatKHR>& availableFormats);

        VkPresentModeKHR ChooseSwapPresentMode(
                const std::vector<VkPresentModeKHR> availablePresentModes);

        VkExtent2D ChooseSwapExtent(
                const VkSurfaceCapabilitiesKHR& capabilities);

        std::vector<char> ReadFile(const std::string& filename);
        VkShaderModule CreateShaderModule(const std::vector<char>& code);

        void CreateDescriptorSetLayout();
        void CreateDescriptorPool();
        void CreateDescriptorSets();

        void CreateSwapChain();
        void CreateImageViews();
        void CreateGraphicsPipeline();
        void CreateRenderPass();
        void CreateFramebuffers();
        void CreateCommandPool();
        void CreateCommandBuffers();
        void CreateSyncObjects();
    };

}  // namespace TandenEngine


#endif  // TANDENENGINE_VULKANINFO_H
