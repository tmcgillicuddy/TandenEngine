//
// Created by thomas.mcgillicuddy on 10/24/2018.
//

#include "Input.h"

namespace TandenEngine {

    Keyboard Input::mKeyboard;

    void Input::GetInput() {
        mKeyboard.UpdateKeyboard();
    }

    bool Input::GetKeyDown(KeyCode key) {
        return mKeyboard.mKeysDown[key].state && !mKeyboard.mPrevKeys[key].state;
    }

    bool Input::GetKey(KeyCode key) {
        return mKeyboard.mKeys[key].state;
    }

    bool Input::GetKeyUp(KeyCode key) {
        return mKeyboard.mKeysUp[key].state && mKeyboard.mPrevKeys[key].state;
    }

}  // namespace TandenEngine
