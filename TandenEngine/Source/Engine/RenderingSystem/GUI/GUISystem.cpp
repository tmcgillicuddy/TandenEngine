//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "GUISystem.h"
#include "imgui.h"

namespace TandenEngine {
    namespace GUI {
        std::vector<GUIElement *> GUISystem::mGuiElements;

        void GUISystem::DrawGUI() {
            //ImGui::NewFrame(); //Marks beginning of gui element allocation
            for (const auto &element: mGuiElements) {
                element->DrawGUI();
            }
            //ImGui::EndFrame(); //Marks end of gui element allocation
            //ImGui::Render(); //Generate vertex buffers of the elements
            //ImDrawData* draw_data = ImGui::GetDrawData(); //Get that rendered data
            //Draw the data to back buffer
        }

        void GUISystem::RegisterGUIElement(GUIElement *newElement) {
            mGuiElements.emplace_back(newElement);
        }

        void GUISystem::InitGUISystem() {
            ImGui::CreateContext();
        }

        void GUISystem::ShutDownGuiSystem() {

        }
    }
}