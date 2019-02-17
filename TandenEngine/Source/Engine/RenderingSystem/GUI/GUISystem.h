//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_GUISYSTEM_H
#define TANDENENGINE_GUISYSTEM_H

#include <vector>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include "GUIElements/GUIHeader.h"

namespace TandenEngine {
    namespace GUI {
        class GUISystem {
            static std::vector<GUIElement *> mGuiElements;  // List of gui elements
            static VkImage fontImage;
            static VkDeviceMemory fontMemory;


            static void InitGUIPipeline();
         public:
            static void InitGUISystem();  // Init the GUI system

            static void ShutDownGuiSystem();
            static void BindGUI();  // Create the buffers for the GUI
            static void UpdateBuffers();  // Update the command buffers


            // Register the GUI elements
            static void RegisterGUIElement(GUIElement *newElement);
        };
    }  // namespace GUI
}  // namespace TandenEngine

#endif  // TANDENENGINE_GUISYSTEM_H
