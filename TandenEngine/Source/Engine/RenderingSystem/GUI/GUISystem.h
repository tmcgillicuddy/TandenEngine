//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_GUISYSTEM_H
#define TANDENENGINE_GUISYSTEM_H

#include <vector>

#include "GUIElement.h"

namespace TandenEngine {

    class GUISystem {
        static std::vector<GUIElement*> mGuiElements;

    public:

        static void DrawGUI();

        static void RegisterGUIElement(GUIElement * newElement);
    };

}

#endif //TANDENENGINE_GUISYSTEM_H
