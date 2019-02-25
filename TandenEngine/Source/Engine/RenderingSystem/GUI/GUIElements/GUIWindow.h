//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#ifndef TANDENEDITOR_WINDOW_H
#define TANDENEDITOR_WINDOW_H

#include "GUIElement.h"

namespace TandenEngine {
    namespace GUI {
        class GUIWindow : public GUIElement {
            std::string mWindowName;
            bool mShow = true;
            ImGuiWindowFlags mFlags;
        public:
            GUIWindow(char * name,  ImGuiWindowFlags flags);
            void DrawGUI() override;
        };

    }
}
#endif //TANDENEDITOR_WINDOW_H
