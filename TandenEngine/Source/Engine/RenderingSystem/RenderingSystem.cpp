//
// Created by thomas.mcgillicuddy on 10/31/2018.
//

#include "RenderingSystem.h"

namespace TandenEngine {


    VkInstance RenderingSystem::VulkanInstance;

    std::vector<Renderer *> RenderingSystem::mRenderers;

    Window*  RenderingSystem::testWindow;

    void RenderingSystem::Draw() {
        for (const auto &rend : mRenderers) {
            rend->Draw();
        }

        PollWindowEvents();

    }

    void RenderingSystem::RegisterRenderer(Renderer *newRenderer) {
        mRenderers.emplace_back(newRenderer);
    }


    void RenderingSystem::InitSystem()
    {
        InitGLFW();
        InitVulkan();
        InitWindow(800, 600, "eat my ass");
    }

    void RenderingSystem::InitGLFW()
    {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    }

    void RenderingSystem::InitVulkan()
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




        //pick physical device

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

        vkDestroyInstance(VulkanInstance, nullptr);

        glfwDestroyWindow(testWindow->GetWindowRef());

        glfwTerminate();
    }

}