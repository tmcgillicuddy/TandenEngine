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
            UpdateUniformBuffers();

            // Render Command buffers
            // std::cout << "render \n" ;
            // Render();
            // std::cout << "success \n" ;

            // Poll window events
            PollWindowEvents();

            // Present Render
            std::cout << "present \n" ;
            SubmitFrame();
            std::cout << "present successful \n" ;

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

        VkCommandBufferBeginInfo cmdBufInfo = {};
        cmdBufInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        // configure render pass for command buffer
        VkRenderPassBeginInfo renderPassInfo = {};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = mVulkanInfo.renderPass;
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

                    // Bind Vertex Buffer on Model
                    vkCmdBindVertexBuffers(cmdBuffer, 0, 1,
                            &meshRend->mpMesh->mModelResource->mVertexBuffer.mBuffer, offsets);

                    // Bind Index Buffer on Model
                    vkCmdBindIndexBuffer(cmdBuffer,
                            meshRend->mpMesh->mModelResource->mIndexBuffer.mBuffer,
                                         0, VK_INDEX_TYPE_UINT32);

                    // TODO(Rosser) it's breaking here
                    // Bind Uniform buffer on Mesh Renderer
                    vkCmdBindDescriptorSets(cmdBuffer,
                                            VK_PIPELINE_BIND_POINT_GRAPHICS, mVulkanInfo.pipelineLayout, 0, 1,
                                            meshRend->mDescriptorSet, 0, NULL);
                    //std::cout << "bind descriptor sets successful, prepare to draw \n";

                    vkCmdDrawIndexed(cmdBuffer,
                            meshRend->mpMesh->mModelResource->mIndices.size(), 1, 0, 0, 0);

                    //std::cout << "draw indexed successful \n";
                    //system("pause");

                }
            }
            // GUI uses different graphics pipeline, so draw buffers differently
            // GUI::GUISystem::DrawGUI(cmdBuffer);

            vkCmdEndRenderPass(cmdBuffer);

            Debug::CheckVKResult(vkEndCommandBuffer(cmdBuffer));
        }
    }

	void RenderingSystem::UpdateCommandBuffers()
	{
		mVulkanInfo.UpdateCommandBuffers();
	}

	std::vector<Renderer *> RenderingSystem::GetRenderers()
	{
		return mRenderers;
	}

	void RenderingSystem::SubmitFrame() {

		// reset fences
		// vkWaitForFences(
		// mVulkanInfo.logicalDevice, 1,
		// &mVulkanInfo.inFlightFences[mVulkanInfo.currentFrame], 
		// VK_TRUE, std::numeric_limits<uint64_t>::max());

		// get next image from swapchain and trigger avaliable semaphore
		VkResult result = vkAcquireNextImageKHR(
			mVulkanInfo.logicalDevice,
			mVulkanInfo.swapChain,
			std::numeric_limits<uint64_t>::max(),
			mVulkanInfo.imageAvailableSemaphores[0], //mVulkanInfo.currentFrame],
                VK_NULL_HANDLE, &mImageIndex);


        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            //mVulkanInfo.framebufferResized = false;
            mVulkanInfo.RecreateSwapChain();
            return;
        } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            Debug::CheckVKResult(result);
        }
        
		// determine which semaphores wait on eachother
		VkSemaphore waitSemaphores[] =
		{ mVulkanInfo.imageAvailableSemaphores[0] };//mVulkanInfo.currentFrame]}; //testing with 1 frame
			VkSemaphore signalSemaphores[] =
		{ mVulkanInfo.renderFinishedSemaphores[0] };//mVulkanInfo.currentFrame]}; //testing with 1 frame

        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

        // info for submission to queue
        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &mVulkanInfo.commandBuffers[0]; //mImageIndex];
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        // vkResetFences(
        //        mVulkanInfo.logicalDevice,
        //        1,
        //        &mVulkanInfo.inFlightFences[mVulkanInfo.currentFrame]);

        // Submit To Queue
        if (vkQueueSubmit(mVulkanInfo.gfxQueue, 1, &submitInfo, VK_NULL_HANDLE) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        // presentation info

        mVulkanInfo.presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        mVulkanInfo.presentInfo.waitSemaphoreCount = 1;
        mVulkanInfo.presentInfo.pWaitSemaphores = signalSemaphores;
        mVulkanInfo.presentInfo.swapchainCount = 1;
        mVulkanInfo.presentInfo.pSwapchains = &mVulkanInfo.swapChain;
        mVulkanInfo.presentInfo.pImageIndices = &mImageIndex;
        // not necessary with one swapchain but this checks
        // if all swapchain presentation was successful or not
		//mVulkanInfo.presentInfo.pResults = nullptr;

        // present image to swapchain
        vkQueuePresentKHR(mVulkanInfo.presentationQueue, &mVulkanInfo.presentInfo);

        //vkQueueWaitIdle(mVulkanInfo.presentationQueue);

        // increment frames (only needed for fences)
        mVulkanInfo.currentFrame = (mVulkanInfo.currentFrame + 1) % mVulkanInfo.maxFramesInFlight;
    }

    void RenderingSystem::UpdateUniformBuffers() {
        mvpUniforms ubo;

        // Set Main Camera Info for perspective
        if (mMainCam) {
        } else {  
			// Use default vals
            // TODO(Nils/Rosser) Set projection and view matrix
            // ubo.projection // Default to 60 degree FOV
            // ubo.view  // Default to origin
        }
        // Update Uniform Buffers
        for (const auto &rend : mRenderers) {
            if (MeshRenderer *meshRend = dynamic_cast<MeshRenderer *>(rend)) {
//                ubo.model = mat4(1);
                // TODO(Anyone) Set model to transform data of mesh renderer
                memcpy(meshRend->mUniformBuffer.mMapped, &ubo, sizeof(ubo));
            }
        }
    }
}  // namespace TandenEngine
