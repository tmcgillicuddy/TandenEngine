//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#include "GUIElement.h"
#include "GUISystem.h"

namespace TandenEngine {

    void GUIElement::RegisterGUI() {
        GUISystem::RegisterGUIElement(this);
    }

    GUIElement::GUIElement() {
        RegisterGUI();
    }

}