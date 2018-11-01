//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "Input.h"

Keyboard Input::mKeyboard;

void Input::GetInput() {
    mKeyboard.UpdateKeyboard();
}
