//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_GUIELEMENT_H
#define TANDENENGINE_GUIELEMENT_H

#include "imgui.h"

namespace TandenEngine {
    class GUIElement {
    public:
        GUIElement();
        virtual void DrawGUI()=0;
        void RegisterGUI();
    };
}

#endif //TANDENENGINE_GUIELEMENT_H
