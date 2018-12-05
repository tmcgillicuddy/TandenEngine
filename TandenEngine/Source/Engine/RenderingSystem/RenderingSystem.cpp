//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include <GLFW/glfw3.h>
#include "RenderingSystem.h"




namespace TandenEngine {


    VkInstance RenderingSystem::VulkanInstance;

    std::vector<Renderer *> RenderingSystem::mRenderers;

    Window* RenderingSystem::testWindow;

    VkPhysicalDevice RenderingSystem::physicalDevice;
    VkDevice RenderingSystem::logicalDevice;
    VkQueue RenderingSystem::gfxQueue;
    VkSurfaceKHR RenderingSystem::windowSurface;

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

        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        //look for queue family with capacity for graphics
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;

        //set priorities for queues, value between 0 and 1 to have priority when queueing events, necessary even if we are only using one queue for event execution
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;


        //check for special device features, like different shader types but right now, again, we dont give a shit
        VkPhysicalDeviceFeatures deviceFeatures = {};

        //create empty info for the new logical device
        VkDeviceCreateInfo newDeviceInfo = {};
        newDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        //
        newDeviceInfo.pQueueCreateInfos = &queueCreateInfo;
        newDeviceInfo.queueCreateInfoCount = 1;

        //give it the empty features object we created
        newDeviceInfo.pEnabledFeatures = &deviceFeatures;

        newDeviceInfo.enabledExtensionCount = 0;

        //create the actual device and set it to our instance of logical device
        if (vkCreateDevice(physicalDevice, &newDeviceInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        //get one queue from queue family of logical device and set it to the graphics queue
        vkGetDeviceQueue(logicalDevice, indices.graphicsFamily.value(), 0, &gfxQueue);



    }

    QueueFamilyIndices RenderingSystem::findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;

        //get queue families supported by target device
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        //load found queue families into a vector
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        //iterate through queue family vec until we find a queue family on the graphcis card that can support VK_QUEUE_GRAPHICS_BIT
        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            ++i;
        }

        return indices;

    }

    void RenderingSystem::InitWindowSurface()
    {
     //   if (glfwCreateWindowSurface(VulkanInstance, testWindow->GetWindowRef(), nullptr, &windowSurface) != VK_SUCCESS) {
     //       throw std::runtime_error("failed to create window surface!");
     //   }
    }

    bool RenderingSystem::SuitableDevice(VkPhysicalDevice targetDevice)
    {
        QueueFamilyIndices indices = findQueueFamilies(targetDevice);

        return indices.isComplete();

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
        vkDestroyInstance(VulkanInstance, nullptr);

        vkDestroyDevice(logicalDevice, nullptr);

        GUI::GUISystem::ShutDownGuiSystem();

        GUI::GUISystem::ShutDownGuiSystem();

        vkDestroyInstance(VulkanInstance, nullptr);

        glfwDestroyWindow(testWindow->GetWindowRef());

        glfwTerminate();
    }

}