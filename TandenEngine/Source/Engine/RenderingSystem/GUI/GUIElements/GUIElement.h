//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_GUIELEMENT_H
#define TANDENENGINE_GUIELEMENT_H

#include <string>
#include <iostream>

#include "imgui.h"

namespace TandenEngine {
    namespace GUI {
        class GUIElement {
         private:
            void RegisterGUI();

         public:
            GUIElement();

            virtual void DrawGUI() = 0;
        };
    }  // namespace GUI
}  // namespace TandenEngine

#endif  // TANDENENGINE_GUIELEMENT_H
