//
// Created by thomas.mcgillicuddy on 12/3/2018.
//

#ifndef TANDENENGINE_TEXT_H
#define TANDENENGINE_TEXT_H

#include "../GUIElement.h"

namespace TandenEngine {
    namespace GUI {

        class Text : public GUIElement {
        private:
            std::string text = "";
        public:
            Text(std::string);
            void DrawGUI() override;
        };

    }
}
#endif //TANDENENGINE_TEXT_H
