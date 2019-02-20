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

    uint32_t RenderingSystem::mImageIndex;

    void RenderingSystem::DrawWindow() {
        if (!glfwWindowShouldClose(mWindow->GetWindowRef())) {
            // Update Uniforms/Command Buffers
            UpdateBuffers();

            // Render Command buffers
            Debug::Log("Rendering Buffers %n");
            Render();
            Debug::Log("Finished Rendering Buffers %n");
            // Poll window events
            PollWindowEvents();

            // Present Render
            // Debug::LogPause("Presenting Render");
            Present();
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

    void RenderingSystem::Render() {
        // get next image from swapchain and trigger avaliable semaphore
        VkResult result = vkAcquireNextImageKHR(
                mVulkanInfo.logicalDevice,
                mVulkanInfo.swapChain,
                std::numeric_limits<uint64_t>::max(),
                mVulkanInfo.imageAvailableSemaphores[mVulkanInfo.currentFrame],
                VK_NULL_HANDLE, &mImageIndex);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            mVulkanInfo.framebufferResized = false;
            // mVulkanInfo.RecreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            Debug::CheckVKResult(result);
        }

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

        // Draw each model
        for (int32_t i = 0; i < mVulkanInfo.commandBuffers.size(); ++i) {
            // Current Command Buffer
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

            // Foreach renderer
            // - Bind Vertex Buffer
            // - Draw Indexed Buffer
            // TODO(Anyone) use shader(pipeline) attached to material on object(?)
            vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                    mVulkanInfo.graphicsPipeline);
            for (const auto &rend : mRenderers) {
                if (MeshRenderer *meshRend = dynamic_cast<MeshRenderer *>(rend)) {
                    VkDeviceSize offsets[1] = {0};

                    // Bind Uniform buffer on Mesh Renderer
                    vkCmdBindDescriptorSets(cmdBuffer,
                            VK_PIPELINE_BIND_POINT_GRAPHICS, mVulkanInfo.pipelineLayout, 0, 1,
                            &meshRend->mDescriptorSet, 0, NULL);

                    // Bind Vertex Buffer on Model
                    vkCmdBindVertexBuffers(cmdBuffer, 0, 1,
                                           &meshRend->mpMesh
                                           ->mModelResource->mVertexBuffer.mBuffer,offsets);
                    // Bind Index Buffer on Model
                    vkCmdBindIndexBuffer(cmdBuffer,
                            meshRend->mpMesh->mModelResource->mIndexBuffer.mBuffer,
                                         0, VK_INDEX_TYPE_UINT32);
                    vkCmdDrawIndexed(cmdBuffer,
                            meshRend->mpMesh->mModelResource->mIndices.size(), 1, 0, 0, 0);
                }
            }
            // GUI uses different graphics pipeline, so draw buffers differently
            // GUI::GUISystem::DrawGUI(cmdBuffer);

            vkCmdEndRenderPass(cmdBuffer);

            Debug::CheckVKResult(vkEndCommandBuffer(cmdBuffer));
        }
    }

    void RenderingSystem::Present() {
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
        submitInfo.pCommandBuffers = &mVulkanInfo.commandBuffers[mImageIndex];

        // determine which semaphore will signal once command buffer finishes
        VkSemaphore signalSemaphores[] =
                {mVulkanInfo.renderFinishedSemaphores[mVulkanInfo.currentFrame]};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

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
        presentInfo.pImageIndices = &mImageIndex;

        // not necessary with one swapchain but this checks
        // if all swapchain presentation was successful or not
        presentInfo.pResults = nullptr;  //  Optional

        // present image to swapchain
        vkQueuePresentKHR(mVulkanInfo.presentationQueue, &presentInfo);

        vkQueueWaitIdle(mVulkanInfo.presentationQueue);

        // increment frames
        mVulkanInfo.currentFrame = (mVulkanInfo.currentFrame + 1) % mVulkanInfo.maxFramesInFlight;
    }

    void RenderingSystem::UpdateBuffers() {
        mvpubo ubo;

        // Set Main Camera Info for perspective
        if (mMainCam) {
        } else {  // Use default vals
            // TODO(Nils/Rosser) Set projection and view matrix
            // ubo.projection // Default to 60 degree FOV
            // ubo.view  // Default to origin
        }
        // Update Uniform Buffers
        for (const auto &rend : mRenderers) {
            if (MeshRenderer *meshRend = dynamic_cast<MeshRenderer *>(rend)) {
                ubo.model = mat4(1);
                // TODO(Anyone) Set model to transform data of mesh renderer
                memcpy(meshRend->mUniformBuffer.mMapped, &ubo, sizeof(ubo));
            }
        }

        // Recreate command buffers
        mVulkanInfo.commandBuffers.resize(mVulkanInfo.swapChainFramebuffers.size());

        // create command buffer info
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = mVulkanInfo.commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t) mVulkanInfo.commandBuffers.size();
        // throw if failed allocation
        if (vkAllocateCommandBuffers(
                mVulkanInfo.logicalDevice,
                &allocInfo,
                mVulkanInfo.commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
        }
    }
}  // namespace TandenEngine
