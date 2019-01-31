//
// Created by thomas.mcgillicuddy on 10/31/2018.
//
#define GLFW_INCLUDE_VULKAN

#include "../../Core/Debugger/Debug.h"
#include "RenderingSystem.h"

namespace TandenEngine {


    std::vector<Renderer *> RenderingSystem::mRenderers;

    Window* RenderingSystem::mWindow;

    VulkanInfo RenderingSystem::mVulkanInfo;

    void RenderingSystem::Draw()
    {
        if (!glfwWindowShouldClose(mWindow->GetWindowRef())) {

            //Draw gameobject renderers
            for (const auto &rend : mRenderers) {
                rend->Draw(); //fix draw to PROVIDE resources so this function (RenderingSystem::Draw) actually draws instead of each object drawing thmeselves
            }



            //Draw GUI Elements
            GUI::GUISystem::DrawGUI();

            PollWindowEvents();
            DrawWindow();
        }

        //vkDeviceWaitIdle(logicalDevice);
    }

    void RenderingSystem::RegisterRenderer(Renderer *newRenderer)
    {
        mRenderers.emplace_back(newRenderer);
    }

    void RenderingSystem::InitSystem()
    {
        InitGLFW();
        InitWindow(windowWidth, windowHeight, "Tanden Engine");
        mVulkanInfo.InitVulkan();

        GUI::GUISystem::InitGUISystem();
    }

    void RenderingSystem::InitGraphicsPipeline() {
        mVulkanInfo.InitVulkanPipeline();
    }


    void RenderingSystem::InitGLFW()
    {

        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    }

    void RenderingSystem::InitWindow(int windowWidth, int windowHeight, std::string windowName)
    {
        //create test window

        mWindow = new Window(windowWidth, windowHeight, windowName);

        mWindow->initWindow();
    }

    void RenderingSystem::PollWindowEvents()
    {
        glfwPollEvents();
    }

    void RenderingSystem::Cleanup() {
        //Bring it on! I'll destroy you all!

        //TODO move vulkan specific clean up to vulkaninfo class
        vkDestroySemaphore(mVulkanInfo.logicalDevice, mVulkanInfo.renderFinishedSemaphore, nullptr);
        vkDestroySemaphore(mVulkanInfo.logicalDevice, mVulkanInfo.imageAvailableSemaphore, nullptr);

        vkDestroyCommandPool(mVulkanInfo.logicalDevice, mVulkanInfo.commandPool, nullptr);

        for (auto framebuffer : mVulkanInfo.swapChainFramebuffers) {
            vkDestroyFramebuffer(mVulkanInfo.logicalDevice, framebuffer, nullptr);
        }

        vkDestroyPipeline(mVulkanInfo.logicalDevice, mVulkanInfo.graphicsPipeline, nullptr);
        vkDestroyPipelineLayout(mVulkanInfo.logicalDevice, mVulkanInfo.pipelineLayout, nullptr);
        vkDestroyRenderPass(mVulkanInfo.logicalDevice, mVulkanInfo.renderPass, nullptr);

        for (auto imageView : mVulkanInfo.swapChainImageViews) {
            vkDestroyImageView(mVulkanInfo.logicalDevice, imageView, nullptr);
        }

        vkDestroyPipelineLayout(mVulkanInfo.logicalDevice, mVulkanInfo.pipelineLayout, nullptr);

        GUI::GUISystem::ShutDownGuiSystem();

        vkDestroySurfaceKHR(mVulkanInfo.VulkanInstance, mVulkanInfo.WindowSurface, nullptr);

        vkDestroySwapchainKHR(mVulkanInfo.logicalDevice, mVulkanInfo.swapChain, nullptr);

        vkDestroyDevice(mVulkanInfo.logicalDevice, nullptr);

        vkDestroyInstance(mVulkanInfo.VulkanInstance, nullptr);

        glfwDestroyWindow(mWindow->GetWindowRef());

        glfwTerminate();
    }

    const VulkanInfo *RenderingSystem::GetVulkanInfo() {
        return &mVulkanInfo;
    }

    Window *RenderingSystem::GetWindow() {
        return mWindow;
    }


}