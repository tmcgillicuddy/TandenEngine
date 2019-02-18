//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_GUISYSTEM_H
#define TANDENENGINE_GUISYSTEM_H

#include <vector>

#include "imgui.h"
#include "imgui_internal.h"
#include "NilsMath.h"
#include "GUIElements/GUIHeader.h"
#include "../../ResourceManager/BufferManager/Buffer.h"

namespace TandenEngine {
    namespace GUI {
        class GUISystem {
            static std::vector<GUIElement *> mGuiElements;  // List of gui elements
            static VkImage fontImage;
            static VkDeviceMemory fontMemory;
            static Buffer mVertexBuffer;
            static Buffer mIndexBuffer;
            static int32_t mVertexCount; // Count of all vertices in GUI
            static int32_t mIndexCount; // Count of all indices in GUI

            static void InitGUIPipeline();

            struct PushConstBlock {
                vec2 scale;
                vec2 translate;
            } pushConstBlock;

         public:
            static void InitGUISystem();  // Init the GUI system

            static void ShutDownGuiSystem();
            static void BindGUI();  // Create the buffers for the GUI
            static void UpdateBuffers();  // Update the vertex/index buffers
            static void DrawGUI(VkCommandBuffer commandBuffer);  // Draw the GUI command buffers

            // Register the GUI elements
            static void RegisterGUIElement(GUIElement *newElement);
        };
    }  // namespace GUI
}  // namespace TandenEngine

#endif  // TANDENENGINE_GUISYSTEM_H
