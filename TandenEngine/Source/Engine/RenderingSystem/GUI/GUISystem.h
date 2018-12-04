//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_GUISYSTEM_H
#define TANDENENGINE_GUISYSTEM_H

#include <vector>

#include "imgui.h"
#include "imgui_internal.h"
#include "GUIElements/GUIElement.h"

namespace TandenEngine {
    namespace GUI {
        class GUISystem {
            static std::vector<GUIElement *> mGuiElements; //List of gui elements
            static ImGuiIO* io; //ImGui io struct, filled with Tanden data
            
        public:

            static void InitGUISystem(); //Init the GUI system

            static void ShutDownGuiSystem();

            static void DrawGUI(); //Draw GUI elements

            static void RegisterGUIElement(GUIElement *newElement); //Register the GUI elements
        };
    }
}

#endif //TANDENENGINE_GUISYSTEM_H
