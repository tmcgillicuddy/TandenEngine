//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "GUISystem.h"
#include "imgui.h"
namespace TandenEngine
{
    std::vector<GUIElement *> GUISystem::mGuiElements;

    void GUISystem::DrawGUI() {
        for (const auto &element: mGuiElements)
        {
            element->DrawGUI();
        }
    }

    void GUISystem::RegisterGUIElement(GUIElement *newElement) {
        mGuiElements.emplace_back(newElement);
    }
}