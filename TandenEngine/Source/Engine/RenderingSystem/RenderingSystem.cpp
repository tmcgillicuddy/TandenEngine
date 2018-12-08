//
// Created by thomas.mcgillicuddy on 10/31/2018.
//
#define GLFW_INCLUDE_VULKAN

#include "RenderingSystem.h"

namespace TandenEngine {


    VkInstance RenderingSystem::VulkanInstance;

    std::vector<Renderer *> RenderingSystem::mRenderers;

    Window* RenderingSystem::testWindow;

    VkPhysicalDevice RenderingSystem::physicalDevice;
    VkDevice RenderingSystem::logicalDevice;
    VkQueue RenderingSystem::gfxQueue;
    VkSurfaceKHR RenderingSystem::WindowSurface;
    VkQueue RenderingSystem::presentationQueue;

    void RenderingSystem::Draw()
    {
        //Draw gameobject renderers
        for (const auto &rend : mRenderers) {
            rend->Draw();
        }

        //Draw GUI Elements
        GUI::GUISystem::DrawGUI();

        PollWindowEvents();

    }

    void RenderingSystem::RegisterRenderer(Renderer *newRenderer)
    {
        mRenderers.emplace_back(newRenderer);
    }

    void RenderingSystem::InitSystem()
    {
        InitGLFW();
        InitVulkan();
        InitWindow(800, 600, "eat my ass");

        GUI::GUISystem::InitGUISystem();
    }

    void RenderingSystem::InitGLFW()
    {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    }

    void RenderingSystem::InitVulkan()
    {
        InitVKInstance();
        InitWindowSurface();
        SelectPhysicalDevice();
        InitLogicalDevice();
        CreateSwapChain();
        CreateImageViews();
//        CreateGraphicsPipeline();

    }

    void RenderingSystem::InitVKInstance()
    {

        //create instance
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &VulkanInstance);

        if (vkCreateInstance(&createInfo, nullptr, &VulkanInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

    }

    void RenderingSystem::SelectPhysicalDevice()
    {

        physicalDevice = VK_NULL_HANDLE;

        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(VulkanInstance , &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(VulkanInstance, &deviceCount, devices.data());

        for (const auto& device : devices) {
            if (SuitableDevice(device)) {
                physicalDevice = device;
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }

    }

    void RenderingSystem::InitLogicalDevice()
    {

        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);

        //look for queue family with capacity for graphics
        //VkDeviceQueueCreateInfo queueCreateInfo = {};
        //queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        //queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        //queueCreateInfo.queueCount = 1;
        //queueCreateInfo.pQueuePriorities = &queuePriority;

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};


        //set priorities for queues, value between 0 and 1 to have priority when queueing events, necessary even if we are only using one queue for event execution
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }


        //check for special device features, like different shader types but right now, again, we dont give a shit
        VkPhysicalDeviceFeatures deviceFeatures = {};

        //create empty info for the new logical device
        VkDeviceCreateInfo newDeviceInfo = {};
        newDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        //info queue
        newDeviceInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        newDeviceInfo.pQueueCreateInfos = queueCreateInfos.data();

        //give it the empty features object we created
        newDeviceInfo.pEnabledFeatures = &deviceFeatures;

        newDeviceInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions.size());
        newDeviceInfo.ppEnabledExtensionNames = DeviceExtensions.data();

        //create the actual device and set it to our instance of logical device
        if (vkCreateDevice(physicalDevice, &newDeviceInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        //get one queue from queue family of logical device and set it to the graphics queue
        vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &gfxQueue);
        vkGetDeviceQueue(logicalDevice, indices.presentFamily.value(), 0, &presentationQueue);
    }

    QueueFamilyIndices RenderingSystem::FindQueueFamilies(VkPhysicalDevice targetDevice)
    {
        QueueFamilyIndices indices;

        //get queue families supported by target device
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(targetDevice, &queueFamilyCount, nullptr);

        //load found queue families into a vector
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(targetDevice, &queueFamilyCount, queueFamilies.data());

        //iterate through queue family vec until we find a queue family on the graphcis card that can support VK_QUEUE_GRAPHICS_BIT
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(targetDevice, i, WindowSurface, &presentSupport);

            if (queueFamily.queueCount > 0 && presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            ++i;
        }

        return indices;
    }

    bool RenderingSystem::CheckDeviceExtSupport(VkPhysicalDevice targetDevice) {

        //find number of supported extensions
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(targetDevice, nullptr, &extensionCount, nullptr);

        //create list of extensions based on how many are supported for that device
        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(targetDevice, nullptr, &extensionCount, availableExtensions.data());

        //convert renderingsystem requirements into a set of strings
        std::set<std::string> requiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

        //iterate through both lists to see if the device has the requirements
        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        //return if all the requirements were covered or not
        return requiredExtensions.empty();
    }

    //swapchain
    SwapChainSupportDetails RenderingSystem::PollSwapChainSupport(VkPhysicalDevice targetDevice)
    {
        SwapChainSupportDetails details;


        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(targetDevice, WindowSurface, &details.capabilities);


        //get devices supported window surface formats
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(targetDevice, WindowSurface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(targetDevice, WindowSurface, &formatCount, details.formats.data());
        }

        //get devices supported presentation modes
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(targetDevice, WindowSurface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(targetDevice, WindowSurface, &presentModeCount, details.presentModes.data());
        }
        //TODO finish swapchain bru go to bed lmao





        return details;
    }

    VkSurfaceFormatKHR RenderingSystem::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
            return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
        }

        for (const auto& availableFormat : availableFormats) {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return availableFormat;
            }
        }

        return availableFormats[0];
    }

    VkPresentModeKHR RenderingSystem::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
    {
        VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

        for (const auto& availablePresentMode : availablePresentModes) {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                return availablePresentMode;
            } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                bestMode = availablePresentMode;
            }
        }

        return bestMode;
    }

    VkExtent2D RenderingSystem::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
            return capabilities.currentExtent;
        } else {
            VkExtent2D actualExtent = {windowWidth, windowHeight};

            actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
            actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

            return actualExtent;
        }
    }

    void RenderingSystem::CreateSwapChain() {

        SwapChainSupportDetails swapChainSupport = PollSwapChainSupport(physicalDevice);

        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities);


        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
        if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = WindowSurface;

        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = FindQueueFamilies(physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;

        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(logicalDevice, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, nullptr);
        swapChainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(logicalDevice, swapChain, &imageCount, swapChainImages.data());

        swapChainImageFormat = surfaceFormat.format;
        swapChainExtent = extent;

    }

    void RenderingSystem::CreateImageViews()
    {
        swapChainImageViews.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkImageViewCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = swapChainImages[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = swapChainImageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(logicalDevice, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create image views!");
            }
        }
    }


    void RenderingSystem::InitWindowSurface()
    {
         if (glfwCreateWindowSurface(VulkanInstance, testWindow->GetWindowRef(), nullptr, &WindowSurface) != VK_SUCCESS) {
             throw std::runtime_error("failed to create window surface!");
         }
    }

    bool RenderingSystem::SuitableDevice(VkPhysicalDevice targetDevice)
    {
        QueueFamilyIndices indices = FindQueueFamilies(targetDevice);

        //check for required extensions
        bool extensionsSupported = CheckDeviceExtSupport(targetDevice);

        //check for swapchain support, at least one supported image format and presentation mode
        bool swapChainAdequate = false;

        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = PollSwapChainSupport(targetDevice);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        return indices.isComplete() && extensionsSupported && swapChainAdequate;
    }

    void RenderingSystem::InitWindow(int windowWidth, int windowHeight, std::string windowName)
    {
        //create test window

        testWindow = new Window(windowWidth, windowHeight, windowName);

        testWindow->initWindow();
    }

    void RenderingSystem::PollWindowEvents()
    {
        if (!glfwWindowShouldClose(testWindow->GetWindowRef())) {
            glfwPollEvents();
        }
    }

    void RenderingSystem::Cleanup()
    {
        //Bring it on! I'll destroy you all!
        for (auto imageView : swapChainImageViews) {
            vkDestroyImageView(logicalDevice, imageView, nullptr);
        }

        GUI::GUISystem::ShutDownGuiSystem();

        vkDestroySurfaceKHR(VulkanInstance, WindowSurface, nullptr);

        vkDestroySwapchainKHR(logicalDevice, swapChain, nullptr);

        vkDestroyDevice(logicalDevice, nullptr);

        vkDestroyInstance(VulkanInstance, nullptr);

        glfwDestroyWindow(testWindow->GetWindowRef());

        glfwTerminate();
    }

}