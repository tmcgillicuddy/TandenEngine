//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "GUISystem.h"
#include "imgui.h"

namespace TandenEngine {
    namespace GUI {
        std::vector<GUIElement *> GUISystem::mGuiElements;
        ImGuiIO *GUISystem::io;

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
            std::cout << "Initing GUI System\n";
            ImGui::CreateContext();
            io = &ImGui::GetIO();

            // Build and load the texture atlas into a texture
            // (In the examples/ app this is usually done within the ImGui_ImplXXX_Init() function from one of the demo Renderer)
            int width, height;
            unsigned char *pixels = NULL;
            io->Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
        }

        void GUISystem::ShutDownGuiSystem() {
            // Shutdown
            ImGui::DestroyContext();
            //Test
        }

    }
}