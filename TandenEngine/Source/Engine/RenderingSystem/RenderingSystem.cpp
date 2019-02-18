//
//  Created by thomas.mcgillicuddy on 10/31/2018.
//
#define GLFW_INCLUDE_VULKAN
#define NOMINMAX

#include "Debug.h"
#include "RenderingSystem.h"
#include "../Entity/Components/ComponentHeader.h"

namespace TandenEngine {

    std::vector<Renderer *> RenderingSystem::mRenderers;

    Window* RenderingSystem::mWindow;
    Camera* RenderingSystem::mMainCam;

    VulkanInfo RenderingSystem::mVulkanInfo;

    void RenderingSystem::Draw() {
        if (!glfwWindowShouldClose(mWindow->GetWindowRef())) {
            //Update Uniforms/Command Buffers

            VkCommandBufferBeginInfo cmdBufInfo = {};
            cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            // configure render pass for command buffer
            VkRenderPassBeginInfo renderPassInfo = {};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = mVulkanInfo.mRenderPass;
            // size of render area on screen
            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = mVulkanInfo.swapChainExtent;

            // clear color for render pass
            VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
            renderPassInfo.clearValueCount = 1;
            renderPassInfo.pClearValues = &clearColor;

            //Render Command buffers
            for (int32_t i = 0; i < mVulkanInfo.commandBuffers.size(); ++i) {
                //Current Command Buffer
                VkCommandBuffer cmdBuffer = mVulkanInfo.commandBuffers[i];

                renderPassInfo.framebuffer = mVulkanInfo.swapChainFramebuffers[i];

                Debug::CheckVKResult(vkBeginCommandBuffer(cmdBuffer, &cmdBufInfo));

                vkCmdBeginRenderPass(cmdBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

                VkViewport viewport = {};
                viewport.width = windowWidth;
                viewport.height = windowHeight;
                viewport.minDepth = 0.0f;
                viewport.maxDepth = 1.0f;
                vkCmdSetViewport(cmdBuffer, 0, 1, &viewport);

                VkRect2D scissor = {};
                scissor.extent.width = windowWidth;
                scissor.extent.height = windowHeight;
                scissor.offset.x = 0;
                scissor.offset.y = 0;
                vkCmdSetScissor(cmdBuffer, 0, 1, &scissor);

                vkCmdBindDescriptorSets(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mVulkanInfo.pipelineLayout,
                        0, 1, &mVulkanInfo.descriptorSets[0], 0, NULL);

                // Foreach renderer
                // - Bind Vertex Buffer
                // - Draw Indexed Buffer
                for (const auto &rend : mRenderers) {
                    if (MeshRenderer *meshRend = dynamic_cast<MeshRenderer *>(rend)) {
                        VkDeviceSize offsets[1] = {0};
                        vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, mVulkanInfo.graphicsPipeline);
                        vkCmdBindVertexBuffers(cmdBuffer, 0, 1,
                                               &meshRend->mpMesh->mModelResource->mVertexBuffer.mBuffer, offsets);
                        vkCmdBindIndexBuffer(cmdBuffer, meshRend->mpMesh->mModelResource->mIndexBuffer.mBuffer,
                                             0, VK_INDEX_TYPE_UINT32);
                        vkCmdDrawIndexed(cmdBuffer, meshRend->mpMesh->mModelResource->mIndices.size(), 1, 0, 0, 0);
                    }
                }

                GUI::GUISystem::DrawGUI(cmdBuffer);

                vkCmdEndRenderPass(cmdBuffer);

                Debug::CheckVKResult(vkEndCommandBuffer(cmdBuffer));
            }

            // Present Render

            PollWindowEvents();

            // DrawWindow();
        }
        // vkDeviceWaitIdle(logicalDevice);
    }

    void RenderingSystem::RegisterRenderer(Renderer *newRenderer) {
        mRenderers.emplace_back(newRenderer);
    }

    void RenderingSystem::InitSystem() {
        InitGLFW();
        InitWindow(windowWidth, windowHeight, "Tanden Engine");
        mVulkanInfo.InitVulkan();
    }

    void RenderingSystem::InitGraphicsPipeline() {
        mVulkanInfo.InitVulkanPipeline();
        GUI::GUISystem::InitGUISystem();
    }


    void RenderingSystem::InitGLFW() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }



    void RenderingSystem::InitWindow(int windowWidth, int windowHeight, std::string windowName) {
        // create test window
        mWindow = new Window(windowWidth, windowHeight, windowName);

        mWindow->initWindow();
    }

    void RenderingSystem::PollWindowEvents() {
        glfwPollEvents();
    }

    void RenderingSystem::DrawWindow() {
        // wait for frame to be finished
        // vkWaitForFences(
        //        mVulkanInfo.logicalDevice,
        //        1,
        //        &mVulkanInfo.inFlightFences[mVulkanInfo.currentFrame],
        //        VK_TRUE,
        //        std::numeric_limits<uint64_t>::max());

        // get next image from swapchain and trigger avaliable semaphore
        uint32_t imageIndex;
        VkResult result = vkAcquireNextImageKHR(
                mVulkanInfo.logicalDevice,
                mVulkanInfo.swapChain,
                std::numeric_limits<uint64_t>::max(),
                mVulkanInfo.imageAvailableSemaphores[mVulkanInfo.currentFrame],
                VK_NULL_HANDLE, &imageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            mVulkanInfo.framebufferResized = false;
            mVulkanInfo.RecreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        // info for submission to queue
        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        // determine which semaphores wait on eachother
        VkSemaphore waitSemaphores[] =
                {mVulkanInfo.imageAvailableSemaphores[mVulkanInfo.currentFrame]};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        // determine which command buffers to bind for the color attachment
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &mVulkanInfo.commandBuffers[imageIndex];

        // determine which semaphore will signal once command buffer finishes
        VkSemaphore signalSemaphores[] =
                {mVulkanInfo.renderFinishedSemaphores[mVulkanInfo.currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;
        // std::cout << "draw gui \n";
        // GUI::GUISystem::DrawGUI();
        // reset fences
        vkResetFences(
                mVulkanInfo.logicalDevice,
                1,
                &mVulkanInfo.inFlightFences[mVulkanInfo.currentFrame]);

        // failed to submit
        if (vkQueueSubmit(mVulkanInfo.gfxQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        // presentation info
        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        // which semaphores to wait on for presentation
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        // specify swap chain to present images and the index of the target image
        VkSwapchainKHR swapChains[] = {mVulkanInfo.swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;

        // not necessary with one swapchain but this checks
        // if all swapchain presentation was successful or not
        presentInfo.pResults = nullptr;  //  Optional

        // present image to swapchain
        vkQueuePresentKHR(mVulkanInfo.presentationQueue, &presentInfo);

        vkQueueWaitIdle(mVulkanInfo.presentationQueue);

        // increment frames
        mVulkanInfo.currentFrame = (mVulkanInfo.currentFrame + 1) % mVulkanInfo.maxFramesInFlight;
    }

    void RenderingSystem::Cleanup() {
        // Bring it on! I'll destroy you all!
        mVulkanInfo.CleanupVulkan();

        GUI::GUISystem::ShutDownGuiSystem();

        glfwDestroyWindow(mWindow->GetWindowRef());

        glfwTerminate();
    }

    const VulkanInfo *RenderingSystem::GetVulkanInfo() {
        return &mVulkanInfo;
    }

    Window *RenderingSystem::GetWindow() {
        return mWindow;
    }
}  // namespace TandenEngine
