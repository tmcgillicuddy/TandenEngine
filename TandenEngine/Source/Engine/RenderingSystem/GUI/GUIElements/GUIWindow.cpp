//
// Created by thomas.mcgillicuddy on 2/25/2019.
//

#include "GUIWindow.h"
#include "../GUISystem.h"
namespace TandenEngine {
    namespace GUI {

        void GUIWindow::DrawGUI() {
            if(mShow) {
                ImGui::Begin(mWindowName.c_str(), &mShow, mFlags);

                ImGui::End();
            }
        }

        GUIWindow::GUIWindow(char* name,  ImGuiWindowFlags flags) {
            mWindowName = name;
            mFlags = flags;
        }
    }
}
