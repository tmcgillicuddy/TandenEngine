//
// Created by thomas.mcgillicuddy on 12/3/2018.
//
#define NOMINMAX

#include "GUISystem.h"
#include "../RenderingSystem.h"
#include "Debug.h"

namespace TandenEngine {

    namespace GUI {
        std::vector<GUIElement *> GUISystem::mGuiElements;
        VkImage GUISystem::fontImage = VK_NULL_HANDLE;
        VkDeviceMemory GUISystem::fontMemory = VK_NULL_HANDLE;
        Buffer GUISystem::mVertexBuffer;
        Buffer GUISystem::mIndexBuffer;
        int32_t GUISystem::mVertexCount = 0;
        int32_t GUISystem::mIndexCount = 0;


        void GUISystem::BindGUI() {
            // Start the Dear ImGui frame
            ImGui::NewFrame();

            for (const auto &element : mGuiElements) {
                element->DrawGUI();
            }
            // Test Data
            ImGui::Begin("Hello, world!");
            ImGui::Text("This is some useful text.");
            ImGui::End();

            ImGui::Render();  // Generate the desired buffers
        }

        void GUISystem::UpdateBuffers() {
           // Update render system command buffers
           ImDrawData* drawData = ImGui::GetDrawData();

            // Note: Alignment is done inside buffer creation
            VkDeviceSize vertexBufferSize = drawData->TotalVtxCount * sizeof(ImDrawVert);
            VkDeviceSize indexBufferSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);

            if ((vertexBufferSize == 0) || (indexBufferSize == 0)) {
                return;
            }

            if ((mVertexBuffer.mBuffer == VK_NULL_HANDLE) || (mVertexCount != drawData->TotalVtxCount)) {
                mVertexBuffer.unmap();
                mVertexBuffer.destroy();
                // Debug::CheckVKResult(device->createBuffer(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                // VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &mVertexBuffer, vertexBufferSize));
                mVertexCount = drawData->TotalVtxCount;
                mVertexBuffer.unmap();
                mVertexBuffer.map();
            }

            // Index buffer
            VkDeviceSize indexSize = drawData->TotalIdxCount * sizeof(ImDrawIdx);
            if ((mIndexBuffer.mBuffer == VK_NULL_HANDLE) || (mIndexCount < drawData->TotalIdxCount)) {
                mIndexBuffer.unmap();
                mIndexBuffer.destroy();
                // Debug::CheckVKResult(device->createBuffer(VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                // VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, &mIndexBuffer, indexBufferSize));
                mIndexCount = drawData->TotalIdxCount;
                mIndexBuffer.map();
            }

            // Upload data to command buffers
            ImDrawVert* vtxDst = (ImDrawVert*)mVertexBuffer.mMapped;
            ImDrawIdx* idxDst = (ImDrawIdx*)mIndexBuffer.mMapped;

            for (int n = 0; n < drawData->CmdListsCount; n++) {
                const ImDrawList* cmd_list = drawData->CmdLists[n];
                memcpy(vtxDst, cmd_list->VtxBuffer.Data, cmd_list->VtxBuffer.Size * sizeof(ImDrawVert));
                memcpy(idxDst, cmd_list->IdxBuffer.Data, cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx));
                vtxDst += cmd_list->VtxBuffer.Size;
                idxDst += cmd_list->IdxBuffer.Size;
            }

            // Flush to make writes visible to GPU
            mVertexBuffer.flush();
            mIndexBuffer.flush();
        }

        void GUISystem::InitGUISystem() {
            std::cout << "Initing GUI System\n";
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            // Color scheme TODO(Anyone) find our color scheme
            ImGui::StyleColorsDark();
            // Dimensions
            ImGuiIO& io = ImGui::GetIO();
            io.DisplaySize = ImVec2((float)RenderingSystem::GetWindow()->GetWidth(),
                                    (float)RenderingSystem::GetWindow()->GetHeight());
            io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

            // UI Render Pipeline
            InitGUIPipeline();
        }

        void GUISystem::InitGUIPipeline() {
            VulkanInfo vInfo = *RenderingSystem::GetVulkanInfo();

            VkRenderPass renderPass = vInfo.mRenderPass;
            ImGuiIO& io = ImGui::GetIO();

            // Create font texture
            unsigned char* fontData;
            int texWidth, texHeight;
            io.Fonts->GetTexDataAsRGBA32(&fontData, &texWidth, &texHeight);
            VkDeviceSize uploadSize = texWidth*texHeight * 4 * sizeof(char);

            // Create target image for copy
            VkImageCreateInfo imageInfo {};
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
            imageInfo.extent.width = texWidth;
            imageInfo.extent.height = texHeight;
            imageInfo.extent.depth = 1;
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
            imageInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            Debug::CheckVKResult(vkCreateImage(vInfo.logicalDevice,
                    &imageInfo, nullptr, &fontImage));
            VkMemoryRequirements memReqs;
            vkGetImageMemoryRequirements(vInfo.logicalDevice, fontImage, &memReqs);
            VkMemoryAllocateInfo memAllocInfo {};
            memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
            memAllocInfo.allocationSize = memReqs.size;
            memAllocInfo.memoryTypeIndex = BufferManager::FindMemoryType(memReqs.memoryTypeBits,
                    VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            Debug::CheckVKResult(vkAllocateMemory(vInfo.logicalDevice,
                    &memAllocInfo, nullptr, &fontMemory));
            Debug::CheckVKResult(vkBindImageMemory(vInfo.logicalDevice,
                    fontImage, fontMemory, 0));

            //TODO(Thomas) load gui shaders and save pipeline
        }

        void GUISystem::ShutDownGuiSystem() {
            // Shutdown
            ImGui::DestroyContext();
        }

        void GUISystem::RegisterGUIElement(GUIElement *newElement) {
            mGuiElements.emplace_back(newElement);
        }

        void GUISystem::DrawGUI(VkCommandBuffer commandBuffer) {
            ImGuiIO& io = ImGui::GetIO();

            // vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, nullptr);
            // vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

            // VkViewport viewport = vks::initializers::viewport(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y, 0.0f, 1.0f);
            // vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

            // UI scale and translate via push constants
            // pushConstBlock.scale = vec2(2.0f / io.DisplaySize.x, 2.0f / io.DisplaySize.y);
            // pushConstBlock.translate = vec2(-1.0f, -1.0f);
            // vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(PushConstBlock), &pushConstBlock);

            // Render commands
            ImDrawData* imDrawData = ImGui::GetDrawData();
            int32_t vertexOffset = 0;
            int32_t indexOffset = 0;

            if (imDrawData->CmdListsCount > 0) {

                VkDeviceSize offsets[1] = { 0 };
                vkCmdBindVertexBuffers(commandBuffer, 0, 1, &mVertexBuffer.mBuffer, offsets);
                vkCmdBindIndexBuffer(commandBuffer, mIndexBuffer.mBuffer, 0, VK_INDEX_TYPE_UINT16);

                for (int32_t i = 0; i < imDrawData->CmdListsCount; i++)
                {
                    const ImDrawList* cmd_list = imDrawData->CmdLists[i];
                    for (int32_t j = 0; j < cmd_list->CmdBuffer.Size; j++)
                    {
                        const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[j];
                        VkRect2D scissorRect;
                        scissorRect.offset.x = std::max((int32_t)(pcmd->ClipRect.x), 0);
                        scissorRect.offset.y = std::max((int32_t)(pcmd->ClipRect.y), 0);
                        scissorRect.extent.width = (uint32_t)(pcmd->ClipRect.z - pcmd->ClipRect.x);
                        scissorRect.extent.height = (uint32_t)(pcmd->ClipRect.w - pcmd->ClipRect.y);
                        vkCmdSetScissor(commandBuffer, 0, 1, &scissorRect);
                        vkCmdDrawIndexed(commandBuffer, pcmd->ElemCount, 1, indexOffset, vertexOffset, 0);
                        indexOffset += pcmd->ElemCount;
                    }
                    vertexOffset += cmd_list->VtxBuffer.Size;
                }
            }
        }
    }  // namespace GUI
}  // namespace TandenEngine
