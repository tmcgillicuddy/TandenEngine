//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "GUISystem.h"
#include "../RenderingSystem.h"

namespace TandenEngine {

    namespace GUI {
        std::vector<GUIElement *> GUISystem::mGuiElements;
        ImGuiIO *GUISystem::mIo;
        ImGui_ImplVulkanH_WindowData GUISystem::mWindowData;
        ImGui_ImplVulkan_InitInfo GUISystem::mInitInfo = {};
        ImGui_ImplVulkanH_WindowData *GUISystem::wd;

        void GUISystem::DrawGUI() {
            // Start the Dear ImGui frame
            ImGui_ImplVulkan_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            for (const auto &element : mGuiElements) {
                element->DrawGUI();
            }
            // ImGui::EndFrame(); //Marks end of gui element allocation
            // ImGui::Render(); //Generate vertex buffers of the elements
            // ImDrawData* draw_data = ImGui::GetDrawData(); //Get that rendered data
            // Draw the data to back buffer
            // Rendering
            ImGui::Render();
            // memcpy(&wd->ClearValue.color.float32[0], &clear_color, 4 * sizeof(float));
         //   FrameRender(wd);

        //    FramePresent(wd);
        }

        void GUISystem::RegisterGUIElement(GUIElement *newElement) {
            mGuiElements.emplace_back(newElement);
        }

        void GUISystem::InitGUISystem() {
            std::cout << "Initing GUI System\n";
            wd = &mWindowData;
            SetupVulkanWindowData(wd, RenderingSystem::GetVulkanInfo()->WindowSurface,
                    RenderingSystem::GetWindow()->GetWidth(),
                    RenderingSystem::GetWindow()->GetHeight());

            IMGUI_CHECKVERSION();

            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            ImGui_ImplGlfw_InitForVulkan(RenderingSystem::GetWindow()->GetWindowRef(), true);

            // Set ImGui Vulkan Info
            mInitInfo.Instance = RenderingSystem::GetVulkanInfo()->VulkanInstance;
            mInitInfo.PhysicalDevice = RenderingSystem::GetVulkanInfo()->physicalDevice;
            mInitInfo.Device = RenderingSystem::GetVulkanInfo()->logicalDevice;
            mInitInfo.QueueFamily = 0;  // TODO(Thomas) use queue family (?)
            mInitInfo.Queue = RenderingSystem::GetVulkanInfo()->presentationQueue;
            // mInitInfo.PipelineCache = g_PipelineCache;
            mInitInfo.DescriptorPool = RenderingSystem::GetVulkanInfo()->descriptorPool;
            mInitInfo.Allocator = RenderingSystem::GetVulkanInfo()->mAllocator;
            // mInitInfo.CheckVkResultFn = check_vk_result;
            ImGui_ImplVulkan_Init(&mInitInfo, wd->RenderPass);

            // Setup Style
            ImGui::StyleColorsDark();

            // Build and load the texture atlas into a texture
            // (In the examples/ app this is usually done within
            // the ImGui_ImplXXX_Init() function from one of the demo Renderer)
            VkResult err;
            // Upload Fonts
            {
                // Use any command queue
                VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
                VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

                err = vkResetCommandPool(mInitInfo.Device, command_pool, 0);
                // TODO(Thomas) Error check
                VkCommandBufferBeginInfo begin_info = {};
                begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
                err = vkBeginCommandBuffer(command_buffer, &begin_info);
                // TODO(Thomas) Error check

                ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

                VkSubmitInfo end_info = {};
                end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                end_info.commandBufferCount = 1;
                end_info.pCommandBuffers = &command_buffer;
                err = vkEndCommandBuffer(command_buffer);
                // TODO(Thomas) Error check
                err = vkQueueSubmit(mInitInfo.Queue, 1, &end_info, VK_NULL_HANDLE);
                // TODO(Thomas) Error check

                err = vkDeviceWaitIdle(mInitInfo.Device);
                // TODO(Thomas) Error check
                ImGui_ImplVulkan_InvalidateFontUploadObjects();
            }
        }

        void GUISystem::ShutDownGuiSystem() {
            // Shutdown
        }

        void GUISystem::SetupVulkanWindowData(ImGui_ImplVulkanH_WindowData* wd,
                VkSurfaceKHR surface, int width, int height) {
            wd->Surface = surface;

            // Check for WSI support
            VkBool32 res;
            vkGetPhysicalDeviceSurfaceSupportKHR(RenderingSystem::GetVulkanInfo()->physicalDevice,
                    0, wd->Surface, &res);  // TODO(Thomas) use queue family (?)
            if (res != VK_TRUE) {
                fprintf(stderr, "Error no WSI support on physical device 0\n");
                exit(-1);
            }

            // Select Surface Format
            const VkFormat requestSurfaceImageFormat[] = {
                    VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM,
                    VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM
            };

            const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
            wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(
                    RenderingSystem::GetVulkanInfo()->physicalDevice, wd->Surface,
                    requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat),
                    requestSurfaceColorSpace);

            // Select Present Mode
#ifdef IMGUI_UNLIMITED_FRAME_RATE
            VkPresentModeKHR present_modes[] = {
                    VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR,
                    VK_PRESENT_MODE_FIFO_KHR
            };
#else
            VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
            wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(
                    RenderingSystem::GetVulkanInfo()->physicalDevice,
                    wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));
            // printf("[vulkan] Selected PresentMode = %d\n", wd->PresentMode);

            // Create SwapChain, RenderPass, Framebuffer, etc.
            // TODO(Thomas) use queue family (?)
            ImGui_ImplVulkanH_CreateWindowDataCommandBuffers(
                    RenderingSystem::GetVulkanInfo()->physicalDevice,
                    RenderingSystem::GetVulkanInfo()->logicalDevice, 0, wd,
                    RenderingSystem::GetVulkanInfo()->mAllocator);
            ImGui_ImplVulkanH_CreateWindowDataSwapChainAndFramebuffer(
                    RenderingSystem::GetVulkanInfo()->physicalDevice,
                    RenderingSystem::GetVulkanInfo()->logicalDevice, wd,
                    RenderingSystem::GetVulkanInfo()->mAllocator, width, height);
        }

    }  // namespace GUI
}  // namespace TandenEngine
