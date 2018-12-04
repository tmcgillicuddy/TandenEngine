//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "GUISystem.h"
#include "imgui.h"

namespace TandenEngine {
    namespace GUI {
        std::vector<GUIElement *> GUISystem::mGuiElements;

        void GUISystem::DrawGUI() {
            //ImGui::ShowDemoWindow();
            for (const auto &element: mGuiElements) {
                element->DrawGUI();
            }
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