//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "Input.h"

namespace TandenEngine {

    Keyboard Input::mKeyboard;

    void Input::GetInput() {
        mKeyboard.UpdateKeyboard();
    }

}